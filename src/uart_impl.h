#include "interrupt.h"
#include "os/system_time.h"
#include "peripherals/pps.h"
#include "pic_header.h"
#include "uart.h"
#include "uart_buffer.h"

/* ************************************************************************** */

static uart_config_t *_config;

/* ************************************************************************** */

#define JOIN(x, y) JOIN_AGAIN(x, y)
#define JOIN_AGAIN(x, y) x##y

#define SHORT(x) JOIN(JOIN(U, UARTX), x)
#define LONG(x) JOIN(JOIN(UART, UARTX), x)

/* ************************************************************************** */
// UART transmit

void __interrupt(irq(SHORT(TX)), high_priority) LONG(_TX_ISR)(void) {
    if (tx_buffer_is_empty()) {
        SHORT(TXIE) = 0;
    } else {
        SHORT(TXB) = tx_buffer_read();
    }
}

void LONG(_tx_string)(const char *string, const char terminator) {
    uint16_t currentByte = 0;

    // loop until hitting the provided termination character
    while (string[currentByte] != terminator) {
        while (tx_buffer_is_full()) {
            SHORT(TXIE) = 1;
            delay_ms(20);
        }

        begin_critical_section();
        tx_buffer_write(string[currentByte++]);
        end_critical_section();
    }

    SHORT(TXIE) = 1;
}

void LONG(_tx_char)(char data) {
    while (tx_buffer_is_full()) {
        SHORT(TXIE) = 1;
        delay_ms(20);
    }

    begin_critical_section();
    tx_buffer_write(data);
    end_critical_section();

    SHORT(TXIE) = 1;
}

/* -------------------------------------------------------------------------- */
// UART receive

void __interrupt(irq(SHORT(RX)), high_priority) LONG(_rx_ISR)() {
    if (SHORT(ERRIRbits.PERIF)) {
        char trashcan = SHORT(RXB);
        SHORT(ERRIRbits.PERIF) = 0;
    } else {
        rx_buffer_write(SHORT(RXB));
    }
}

char LONG(_rx_char)(void) {
    char data = 0;

    if (rx_buffer_is_empty()) {
        return '\0';
    }

    begin_critical_section();
    data = rx_buffer_read();
    end_critical_section();

    return data;
}

uint8_t LONG(_rx_available)(void) {
    if (rx_buffer_is_empty()) {
        return 0;
    }

    return 1;
}

/* ************************************************************************** */

void LONG(_tx_set_address)(uint16_t address) {
    SHORT(P1) = address;
    _config->tx_address = address;
}

void LONG(_rx_set_address)(uint16_t address) {
    SHORT(P2) = address;
    _config->rx_address = address;
}

void LONG(_rx_set_address_mask)(uint16_t mask) {
    SHORT(P3) = mask;
    _config->rx_address_mask = mask;
}

/* ************************************************************************** */

static uart_interface_t LONG(_create)(void) {
    uart_interface_t interface;

    // copy the config into the interface struct
    interface.config = _config;

    // set up the interface itself
    interface.tx_string = LONG(_tx_string);
    interface.tx_char = LONG(_tx_char);
    interface.rx_char = LONG(_rx_char);
    interface.rx_available = LONG(_rx_available);
    interface.tx_set_address = LONG(_tx_set_address);
    interface.rx_set_address = LONG(_rx_set_address);
    interface.rx_set_address_mask = LONG(_rx_set_address_mask);

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
    17,   // 921600
    15,   // 1000000
    12,   // 1230000
    11,   // 1333333
    10,   // 1454545
    9,    // 1600000
};

static void LONG(_baud_select)(baud_rate_t baudRate) {
    SHORT(BRG) = baudTable[baudRate];
}

static void LONG(_pps_init)(void) {
    // Only set the PPS pins if the user has actually supplied a value
    if (_config->txPin) {
        JOIN(JOIN(pps_out_UART, UARTX), _TX)(_config->txPin);
    }
    if (_config->rxPin) {
        JOIN(JOIN(pps_in_UART, UARTX), _RX)(_config->rxPin);
    }
}

#define DEFAULT_BUFFER_SIZE 8
static char default_tx_buffer[DEFAULT_BUFFER_SIZE];
static char default_rx_buffer[DEFAULT_BUFFER_SIZE];

uart_interface_t LONG(_init)(uart_config_t *config) {
    _config = config;

    LONG(_baud_select)(_config->baud);
    LONG(_pps_init)();

    if (!_config->tx_buffer || _config->tx_buffer_size < DEFAULT_BUFFER_SIZE) {
        _config->tx_buffer = default_tx_buffer;
        _config->tx_buffer_size = DEFAULT_BUFFER_SIZE;
    }
    tx_buffer_init(_config->tx_buffer, _config->tx_buffer_size);
    if (!_config->rx_buffer || _config->rx_buffer_size < DEFAULT_BUFFER_SIZE) {
        _config->rx_buffer = default_rx_buffer;
        _config->rx_buffer_size = DEFAULT_BUFFER_SIZE;
    }
    rx_buffer_init(_config->rx_buffer, _config->rx_buffer_size);

    SHORT(CON0bits).BRGS = 1; // Baud Rate is set to high speed
    SHORT(CON0bits).TXEN = 1; // Transmit is enabled
    SHORT(CON0bits).RXEN = 1; // Recieve is enabled
    SHORT(CON0bits).MODE = _config->mode;
    if (_config->mode == UART_MODE_ASYNC_9BIT_ADDRESS) {
        LONG(_rx_set_address_mask)(0xff);
    }

    SHORT(RXIE) = 1; // Enable UART Recieve Interrupt

    SHORT(CON1bits).ON = 1; // Enable UART

    return LONG(_create)();
}

#undef JOIN(x, y)
#undef JOIN_AGAIN(x, y)

#undef SHORT(x)
#undef LONG(x)