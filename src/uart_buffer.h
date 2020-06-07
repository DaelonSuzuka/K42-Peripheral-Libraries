#ifndef _UART_BUFFER_H_
#define _UART_BUFFER_H_

#include <stdint.h>

/* ************************************************************************** */

// Circular buffer tools
/*  If UART_BUFFER_SIZE is 256, then the head and tail indexes become
    significantly easier to manage. Bounds checking and modulus operations can
    be replaced a single postincrement(x++) instruction, because a uint8_t
    will wraparound from 0xff to 0x00 on its own.

    Yes, this wastes RAM. No, it doesn't matter, because this project has a
    minimum of 4k of RAM and nothing else has a significant RAM footprint. If
    memory becomes an issue, the size of these buffers can be reduced. This
    would require rewriting the helper macros to add the previously mentioned
    bounds checking.
*/
#define UART_BUFFER_SIZE 256

typedef struct {
    char contents[UART_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
} fast_ring_buffer_t;

#if UART_BUFFER_SIZE == 256
#define buffer_is_empty(buffer) (buffer.head == buffer.tail)
#define buffer_is_full(buffer) ((buffer.head + 1) == buffer.tail)
#define buffer_write(buffer, data) buffer.contents[buffer.head++] = data
#define buffer_read(buffer) buffer.contents[buffer.tail++]
#define buffer_peek_last(buffer) buffer.contents[buffer.head - 1]
#else
#error UART_BUFFER_SIZE other than 256 is not currently supported because the buffer depends on uint8_t overflow behavior
#endif

#endif /* _UART_BUFFER_H_ */