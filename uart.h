#ifndef _UART_H_
#define _UART_H_

#include "peripherals/pps.h"
#include <stdint.h>

/* ************************************************************************** */

typedef enum uart_modes {
    UART_MODE_LIN_MASTER_SLAVE = 0b1100,
    UART_MODE_LIN_SLAVE_ONLY = 0b1011,
    UART_MODE_DMX = 0b1010,
    UART_MODE_DALI_CONTROL_GEAR = 0b1001,
    UART_MODE_DALI_CONTROL_DEVICE = 0b1000,
    UART_MODE_ASYNC_9BIT_ADDRESS = 0b0100,
    UART_MODE_ASYNC_8BIT_EVEN = 0b0011,
    UART_MODE_ASYNC_8BIT_ODD = 0b0010,
    UART_MODE_ASYNC_7BIT = 0b0001,
    UART_MODE_ASYNC_8BIT = 0b0000,
} uart_modes_t;

// UART Baud rates
typedef enum {
    _2400,
    _4800,
    _9600,
    _10417,
    _19200,
    _38400,
    _115200,
    _230400,
    _460800,
    _921600,
    _1000000,
    _1230000,
    _1333333,
    _1454545,
    _1600000,
    _2000000,
    _3200000,
    _4000000,
    _8000000,
    _16000000,
} baud_rate_t;

/* ************************************************************************** */
/*  uart_config_t contains user-modifiable uart settings.

    A config returned by UART_get_config() is set to the default values shown
    below. If different settings are desired, they can be overwrittenbefore the
    config is given to UART_init().
*/
typedef struct {              // default settings
    uint8_t number;           // N/A
    baud_rate_t baud;         // 9600 baud
    uart_modes_t mode;        // UART_MODE_ASYNC_8BIT
    pps_input_t rxPin;        // no PPS selection
    pps_output_t *txPin;      // no PPS selection
    char *tx_buffer;          // N/A
    uint8_t tx_buffer_size;   // N/A
    char *rx_buffer;          // N/A
    uint8_t rx_buffer_size;   // N/A
    uint16_t tx_address;      // N/A
    uint16_t rx_address;      // N/A
    uint16_t rx_address_mask; // N/A
} uart_config_t;

// return a UART config populated with default values
#define UART_get_config(uartNumber)                                            \
    { uartNumber, _9600, UART_MODE_ASYNC_8BIT }

/* ************************************************************************** */
// UART buffer helper macros

#define create_tx_buffer(name, config, size)                                   \
    do {                                                                       \
        static char name##_tx_buffer[size];                                    \
        config.tx_buffer = name##_tx_buffer;                                   \
        config.tx_buffer_size = size;                                          \
    } while (0);

#define create_rx_buffer(name, config, size)                                   \
    do {                                                                       \
        static char name##_rx_buffer[size];                                    \
        config.rx_buffer = name##_rx_buffer;                                   \
        config.rx_buffer_size = size;                                          \
    } while (0);

#define create_uart_buffers(name, config, size)                                \
    do {                                                                       \
        create_tx_buffer(name, config, size);                                  \
        create_rx_buffer(name, config, size);                                  \
    } while (0);

/* -------------------------------------------------------------------------- */
/*  uart_interface_t provides an abstract interface to the UART peripherals.

    Creating an interface object without initilizing it is useless, and probably
    results in undefined behavior. Take care to only use a uart_interface_t that
    has been properly initialized by UART_init().
*/
// UART dummy functions

extern void dummy_tx_string(const char *string, const char terminator);
extern void dummy_tx_char(char data);
extern char dummy_rx_char(void);
extern uint8_t dummy_rx_available(void);
extern void dummy_tx_set_address(uint16_t address);
extern void dummy_rx_set_address(uint16_t address);
extern void dummy_rx_set_address_mask(uint16_t mask);

typedef struct {
    void (*tx_string)(const char *, const char);
    void (*tx_char)(char);
    char (*rx_char)(void);
    uint8_t (*rx_available)(void);
    void (*tx_set_address)(uint16_t address);
    void (*rx_set_address)(uint16_t address);
    void (*rx_set_address_mask)(uint16_t mask);
    uart_config_t *config; // must be last so EMPTY_UART_INTERFACE() can work
} uart_interface_t;

#define EMPTY_UART_INTERFACE(name)                                             \
    static uart_interface_t uart = {                                           \
        dummy_tx_string,           dummy_tx_char,        dummy_rx_char,        \
        dummy_rx_available,        dummy_tx_set_address, dummy_rx_set_address, \
        dummy_rx_set_address_mask,                                             \
    }

/* ************************************************************************** */
/*  UART configuration and initilization

    The purpose of this UART driver is to allow for easy dependency injection.
    These projects have a decent volume of code that lives in shared libraries,
    and should remain insulated from project changes. Instead of a shared
    library module managing the setup of the UART it needs, now the UART can be
    initialized at the very top level, in the project code, and the resulting
    uart_interface_t object can be passed into the library's init function.

    In short, project level changes (which UART is used by which module, which
    pins that UART needs to use) can be left entirely in the project level code.

    Here's an example of initializing a module that requires a UART:

    UART2 will be configured to operate at 115200 baud, transmit on pin C4, and
    recieve on pin C5. The resulting interface object is then given to the
    module's init function.

    step 1: configuration
    uart_config_t config = UART_get_config(2);
    config.baud = _115200;
    config.txPin = &RC4PPS;
    config.rxPin = (PPS_PORT_C & PPS_PIN_5);

    step 2: initialization
    uart_interface_t uart = UART_init(config);
    module_init(uart);
*/
// Return a config object with default values
// extern uart_config_t UART_get_config(uint8_t uartNumber);

// Accepts a config object and returns a uart interface object
extern uart_interface_t UART_init(uart_config_t *config);

/* ************************************************************************** */
/*  Using UART interface objects

    Previous versions of this UART driver exposed an API similar to this:

    extern void UART1_init(baud_rate_t baud);
    extern void UART1_tx_char(char data);
    extern char UART2_rx_char(void);

    This API would be used like this:
    UART1_init(_9600);
    UART1_tx_char(data);
    char data = UART2_rx_char();

    This is straightforward, but it made it difficult to decouple shared library
    code from the specifics of an individual UART.

    The new UART interface object behaves a little more like an instance of a
    class. Assuming that the default UART configuration is acceptable, creating
    a new UART interface looks like this:

    uart_interface_t uart1 = UART_init(UART_get_config(1));

    Once you have that interface, use it like a "classy" version of the old API:

    uart1.tx_char(data);
    data = uart1.rx_char();
*/

#endif // _UART_H_