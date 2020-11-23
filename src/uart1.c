#include "interrupt.h"
#include "os/system_time.h"
#include "peripherals/pps.h"
#include "pic_header.h"
#include "uart.h"
#include "uart_buffer.h"

/* ************************************************************************** */
// UART1 transmit

/*  Notes on UART1_tx_ISR()

    This function is an Interrupt Vector Table compatible ISR to respond to the
    U1TX interrupt signal. This signal is generated whenever U1TXB is empty and
    U1TXIE is enabled.
*/

// wrappers to make the register accesses easier
#define UART1_TX_IE_enable() U1TXIE = 1
#define UART1_TX_IE_disable() U1TXIE = 0

void __interrupt(irq(U1TX), high_priority) UART1_tx_ISR() {
    if (tx_buffer_is_empty()) {
        UART1_TX_IE_disable();
    } else {
        U1TXB = tx_buffer_read();
    }
}

/*  Notes on using UART1_tx_string()

    The following block handles the case when this function overflows the
    UART1_tx_buffer. There are three options for dealing with this input
    overflow:

    1:  Check available space before writing to buffer, and abort and return an
        error if the string won't fit. This doesn't fit with the desired API.
    2:  Silently overwrite the contents of the buffer. This is obviously
        unsatisfactory.
    3:  Block until there's enough room. This is the winner.

    If the buffer is ever full, block until there's enough room to fit the
    remainder of the input string. If there's more string left than BUFFER_SIZE,
    just wait until the buffer is totally empty, then continue filling the
    buffer. This will have an undesirable ping-pong effect until the string is
    over, but that's better than breaking our API or clobbering existing data.
*/
void UART1_tx_string(const char *string, const char terminator) {
    uint16_t currentByte = 0;

    // loop until hitting the provided termination character
    while (string[currentByte] != terminator) {
        while (tx_buffer_is_full()) {
            UART1_TX_IE_enable();
            delay_ms(20);
        }

        begin_critical_section();
        tx_buffer_write(string[currentByte++]);
        end_critical_section();
    }

    UART1_TX_IE_enable();
}

void UART1_tx_char(char data) {
    while (tx_buffer_is_full()) {
        UART1_TX_IE_enable();
        delay_ms(20);
    }

    begin_critical_section();
    tx_buffer_write(data);
    end_critical_section();

    UART1_TX_IE_enable();
}

/* -------------------------------------------------------------------------- */
// UART1 receive

/*  Notes on UART1_rx_ISR()

    This function is an Interrupt Vector Table compatible ISR to respond to the
    U1RX interrupt signal. This signal is generated whenever there is an unread
    byte in U1RXB.
*/

void __interrupt(irq(U1RX), high_priority) UART1_rx_ISR() {
    rx_buffer_write(U1RXB);
}

char UART1_rx_char(void) {
    char data = 0;

    if (rx_buffer_is_empty()) {
        return '\0';
    }

    begin_critical_section();
    data = rx_buffer_read();
    end_critical_section();

    return data;
}

uint8_t UART1_rx_available(void) {
    if (rx_buffer_is_empty()) {
        return 0;
    }

    return rx_buffer.head - rx_buffer.tail;
}

/* ************************************************************************** */

static uart_interface_t UART1_create(uart_config_t config) {
    uart_interface_t interface;

    // copy the config into the interface struct
    interface.config = config;

    // set up the interface itself
    interface.tx_string = UART1_tx_string;
    interface.tx_char = UART1_tx_char;
    interface.rx_char = UART1_rx_char;
    interface.rx_available = UART1_rx_available;

    return interface;
}

static const uint16_t baudTable[] = {
    6666, // 2400
    3332, // 4800
    1666, // 9600
    1535, // 10417
    832,  // 19200
    416,  // 38400
    138,  // 115200
    68,   // 230400
    34,   // 460800
};

static void UART1_baud_select(baud_rate_t baudRate) {
    U1BRG = baudTable[baudRate];
}

static void UART1_pps_init(uart_config_t config) {
    // Only set the PPS pins if the user has actually supplied a value
    if (config.txPin) {
        pps_out_UART1_TX(config.txPin);
    }
    if (config.rxPin) {
        pps_in_UART1_RX(config.rxPin);
    }
}

uart_interface_t UART1_init(uart_config_t config) {
    UART1_baud_select(config.baud);
    UART1_pps_init(config);

    tx_buffer_init(config.tx_buffer, config.tx_buffer_size);
    rx_buffer_init(config.rx_buffer, config.rx_buffer_size);

    U1CON0bits.BRGS = 1; // Baud Rate is set to high speed
    U1CON0bits.TXEN = 1; // Transmit is enabled
    U1CON0bits.RXEN = 1; // Recieve is enabled

    U1RXIE = 1; // Enable UART1 Recieve Interrupt

    U1CON1bits.ON = 1; // Enable UART1

    return UART1_create(config);
}