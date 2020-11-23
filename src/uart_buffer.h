#ifndef _UART_BUFFER_H_
#define _UART_BUFFER_H_

#include <stdbool.h>
#include <stdint.h>

/* ************************************************************************** */

typedef struct {
    volatile char *contents;
    volatile uint8_t head;
    volatile uint8_t tail;
    volatile uint8_t size;
} ring_buffer_t;

/* ************************************************************************** */

static volatile ring_buffer_t tx_buffer;

static void tx_buffer_init(char *contents, uint8_t size) {
    tx_buffer.contents = contents;
    tx_buffer.head = 0;
    tx_buffer.tail = 0;
    tx_buffer.size = size;
}

static bool tx_buffer_is_empty(void) {
    return (tx_buffer.head == tx_buffer.tail); //
}

static bool tx_buffer_is_full(void) {
    uint8_t head = tx_buffer.head + 1;

    if (head == tx_buffer.size) {
        head = 0;
    }

    return (head == tx_buffer.tail);
}

static void tx_buffer_write(char data) {
    tx_buffer.contents[tx_buffer.head++] = data;

    if (tx_buffer.head == tx_buffer.size) {
        tx_buffer.head = 0;
    }
}

static char tx_buffer_read(void) {
    char data = tx_buffer.contents[tx_buffer.tail++];

    if (tx_buffer.tail == tx_buffer.size) {
        tx_buffer.tail = 0;
    }

    return data;
}

// static char tx_buffer_peek_last(void) {
//     uint8_t last = tx_buffer.head - 1;

//     if (last > tx_buffer.size) {
//         last = tx_buffer.size - 1;
//     }

//     return tx_buffer.contents[last];
// }

/* ************************************************************************** */

static volatile ring_buffer_t rx_buffer;

static void rx_buffer_init(char *contents, uint8_t size) {
    rx_buffer.contents = contents;
    rx_buffer.head = 0;
    rx_buffer.tail = 0;
    rx_buffer.size = size;
}

static bool rx_buffer_is_empty(void) {
    return (rx_buffer.head == rx_buffer.tail); //
}

// static bool rx_buffer_is_full(void) {
//     uint8_t head = rx_buffer.head + 1;

//     if (head == rx_buffer.size) {
//         head = 0;
//     }

//     return (head == rx_buffer.tail);
// }

static void rx_buffer_write(char data) {
    rx_buffer.contents[rx_buffer.head++] = data;

    if (rx_buffer.head == rx_buffer.size) {
        rx_buffer.head = 0;
    }
}

static char rx_buffer_read(void) {
    char data = rx_buffer.contents[rx_buffer.tail++];

    if (rx_buffer.tail == rx_buffer.size) {
        rx_buffer.tail = 0;
    }

    return data;
}

// static char rx_buffer_peek_last(void) {
//     uint8_t last = rx_buffer.head - 1;

//     if (last > rx_buffer.size) {
//         last = rx_buffer.size - 1;
//     }

//     return rx_buffer.contents[last];
// }

#endif /* _UART_BUFFER_H_ */