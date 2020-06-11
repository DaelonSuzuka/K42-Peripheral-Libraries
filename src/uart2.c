#include "interrupt.h"
#include "os/system_clock.h"
#include "peripherals/pps.h"
#include "pic_header.h"
#include "uart.h"
#include "uart_buffer.h"

/* ************************************************************************** */
// UART2 transmit

static volatile fast_ring_buffer_t UART2_tx_buffer = {0};

/*  Notes on UART2_tx_ISR()

    This function is an Interrupt Vector Table compatible ISR to respond to the
    U2TX interrupt signal. This signal is generated whenever U2TXB is empty and
    PIE3bits.U2TXIE is enabled. In effect, the interrupt flag is set every time
    UART2 finishes transmitting a byte.
*/

// wrappers to make the register accesses easier
#define UART2_TX_IE_enable() PIE6bits.U2TXIE = 1
#define UART2_TX_IE_disable() PIE6bits.U2TXIE = 0

void __interrupt(irq(U2TX), high_priority) UART2_tx_ISR() {
    if (buffer_is_empty(UART2_tx_buffer)) {
        UART2_TX_IE_disable();
    } else {
        U2TXB = buffer_read(UART2_tx_buffer);
    }
}

/*  Notes on using UART2_tx_string()

    Large or frequent calls to UART2_tx_string() can cause the UART2_tx_buffer
    to overflow. There are three options for dealing with this input overflow:

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
void UART2_tx_string(const char *string, const char terminator) {
    uint16_t currentByte = 0;

    // loop until hitting the provided termination character
    while (string[currentByte] != terminator) {
        while (buffer_is_full(UART2_tx_buffer)) {
            UART2_TX_IE_enable();
            delay_ms(20);
        }

        begin_critical_section();
        buffer_write(UART2_tx_buffer, string[currentByte++]);
        end_critical_section();
    }

    UART2_TX_IE_enable();
}

void UART2_tx_char(char data) {
    while (buffer_is_full(UART2_tx_buffer)) {
        UART2_TX_IE_enable();
        delay_ms(20);
    }

    begin_critical_section();
    buffer_write(UART2_tx_buffer, data);
    end_critical_section();

    UART2_TX_IE_enable();
}

/* -------------------------------------------------------------------------- */
// UART2 receive

static volatile fast_ring_buffer_t UART2_rx_buffer = {0};

/*  Notes on UART2_rx_ISR()

    This function is an Interrupt Vector Table compatible ISR to respond to the
    U2RX interrupt signal. This signal is generated whenever there is an unread
    byte in U2RXB.
*/

void __interrupt(irq(U2RX), high_priority) UART2_rx_ISR() {
    buffer_write(UART2_rx_buffer, U2RXB);
}

char UART2_rx_char(void) {
    if (buffer_is_empty(UART2_rx_buffer)) {
        return 0;
    }

    begin_critical_section();
    char data = buffer_read(UART2_rx_buffer);
    end_critical_section();

    return data;
}

uint8_t UART2_rx_available(void) {
    if (buffer_is_empty(UART2_rx_buffer)) {
        return 0;
    }

    return UART2_rx_buffer.head - UART2_rx_buffer.tail;
}

/* ************************************************************************** */

static uart_interface_t UART2_create(uart_config_t config) {
    uart_interface_t interface;

    // copy the config into the interface struct
    interface.config = config;

    // set up the interface itself
    interface.tx_string = UART2_tx_string;
    interface.tx_char = UART2_tx_char;
    interface.rx_char = UART2_rx_char;
    interface.rx_available = UART2_rx_available;

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
};

static void UART2_baud_select(baud_rate_t baudRate) {
    U2BRG = baudTable[baudRate];
}

static void UART2_pps_init(uart_config_t config) {
    // Only set the PPS pins if the user has actually supplied a value
    if (config.txPin) {
        pps_out_UART2_TX(config.txPin);
    }
    if (config.rxPin) {
        pps_in_UART2_RX(config.rxPin);
    }
}

uart_interface_t UART2_init(uart_config_t config) {
    UART2_baud_select(config.baud);
    UART2_pps_init(config);

    U2CON0bits.BRGS = 1; // Baud Rate is set to high speed
    U2CON0bits.TXEN = 1; // Transmit is enabled
    U2CON0bits.RXEN = 1; // Recieve is enabled

    PIE6bits.U2RXIE = 1; // Enable UART2 Recieve Interrupt

    U2CON1bits.ON = 1; // Enable UART2

    return UART2_create(config);
}