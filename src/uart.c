#include "uart.h"

/* ************************************************************************** */
// UART dummy functions
void dummy_tx_string(const char *string, const char terminator) {
    // intentionally empty body
}
void dummy_tx_char(char data) {
    // intentionally empty body
}
char dummy_rx_char(void) {
    // intentionally empty body, must return something
    return 0;
}
uint8_t dummy_rx_available(void) {
    // intentionally empty body, must return something
    return 0;
}
/* ************************************************************************** */

// return a UART config populated with default values
uart_config_t UART_get_config(uint8_t uartNumber) {
    uart_config_t config;

    config.number = uartNumber;

    // Default settings
    config.baud = _9600; // 9600 baud
    config.txPin = 0;    // no PPS selection
    config.rxPin = 0;    // no PPS selection

    return config;
}

// make sure the linker can find these inits
extern uart_interface_t UART1_init(uart_config_t config);
extern uart_interface_t UART2_init(uart_config_t config);

uart_interface_t UART_init(uart_config_t config) {
    if (config.number == 1) {
        return UART1_init(config);
    } else if (config.number == 2) {
        return UART2_init(config);
    }

    uart_interface_t blankInterface = {0};
    return blankInterface;
}