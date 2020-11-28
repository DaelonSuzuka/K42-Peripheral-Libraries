#ifndef _TIMER_H_
#define _TIMER_H_

#include "pic_header.h"
#include <stdint.h>

/* ************************************************************************** */

// Setup
#define timer0_clock_source(value) T0CON1bits.CS = value
#define timer0_prescale(value) T0CON1bits.CKPS = value
#define timer0_postscale(value) T0CON0bits.OUTPS = value
#define timer0_clock_sync_enable() T0CON1bits.ASYNC = 1
#define timer0_clock_sync_disable() T0CON1bits.ASYNC = 0

// General manipulation
#define timer0_start() T0EN = 1
#define timer0_stop() T0EN = 0
#define timer0_clear()                                                         \
    do {                                                                       \
        TMR0H = 0x00;                                                          \
        TMR0L = 0x00;                                                          \
    } while (0)
#define timer0_read() (((uint16_t)TMR0H << 8) | (uint16_t)TMR0L)

// Interrupt control
#define timer0_interrupt_enable() TMR0IE = 1
#define timer0_interrupt_disable() TMR0IE = 0
#define timer0_IF_clear() TMR0IF = 0
#define timer0_IF_read() TMR0IF

// Other features
#define timer0_period_set(value) TMR0H = value // only in 8bit mode

/* -------------------------------------------------------------------------- */

// Setup
#define timer1_clock_source(value) T1CLK = value
#define timer1_prescale(value) T1CONbits.CKPS = value
#define timer1_clock_sync_enable() T1CONbits.NOT_SYNC = 0
#define timer1_clock_sync_disable() T1CONbits.NOT_SYNC = 1

// General manipulation
#define timer1_start() TMR1ON = 1
#define timer1_stop() TMR1ON = 0
#define timer1_clear()                                                         \
    do {                                                                       \
        TMR1H = 0x00;                                                          \
        TMR1L = 0x00;                                                          \
    } while (0)
#define timer1_read() (((uint16_t)TMR1H << 8) | (uint16_t)TMR1L)

// Interrupt control
#define timer1_interrupt_enable() TMR1IE = 1
#define timer1_interrupt_disable() TMR1IE = 0
#define timer1_IF_clear() TMR1IF = 0
#define timer1_IF_read() TMR1IF

// Other features
#define timer1_gate_enable() T1GE = 1
#define timer1_gate_disable() T1GE = 0

/* -------------------------------------------------------------------------- */

// Setup
#define timer2_clock_source(value) T2CLK = value
#define timer2_prescale(value) T2CONbits.CKPS = value
#define timer2_postscale(value) T2CONbits.OUTPS = value

// General manipulation
#define timer2_start() TMR2ON = 1
#define timer2_stop() TMR2ON = 0
#define timer2_clear() TMR2 = 0x00;
#define timer2_read() TMR2

// Interrupt control
#define timer2_interrupt_enable() TMR2IE = 1
#define timer2_interrupt_disable() TMR2IE = 0
#define timer2_IF_clear() TMR2IF = 0
#define timer2_IF_read() TMR2IF

// Other features
#define timer2_period_set(value) PR2 = value

/* -------------------------------------------------------------------------- */

// Setup
#define timer3_clock_source(value) T3CLK = value
#define timer3_prescale(value) T3CONbits.CKPS = value
#define timer3_clock_sync_enable() T3CONbits.NOT_SYNC = 0
#define timer3_clock_sync_disable() T3CONbits.NOT_SYNC = 1

// General manipulation
#define timer3_start() TMR3ON = 1
#define timer3_stop() TMR3ON = 0
#define timer3_clear()                                                         \
    do {                                                                       \
        TMR3H = 0x00;                                                          \
        TMR3L = 0x00;                                                          \
    } while (0)
#define timer3_read() (((uint16_t)TMR3H << 8) | (uint16_t)TMR3L)

// Interrupt control
#define timer3_interrupt_enable() TMR3IE = 1
#define timer3_interrupt_disable() TMR3IE = 0
#define timer3_IF_clear() TMR3IF = 0
#define timer3_IF_read() TMR3IF

// Other features
#define timer3_gate_enable() T3GE = 1
#define timer3_gate_disable() T3GE = 0

/* -------------------------------------------------------------------------- */

// Setup
#define timer4_clock_source(value) T4CLK = value
#define timer4_prescale(value) T4CONbits.CKPS = value
#define timer4_postscale(value) T4CONbits.OUTPS = value

// General manipulation
#define timer4_start() TMR4ON = 1
#define timer4_stop() TMR4ON = 0
#define timer4_clear() TMR4 = 0x00;
#define timer4_read() TMR4

// Interrupt control
#define timer4_interrupt_enable() TMR4IE = 1
#define timer4_interrupt_disable() TMR4IE = 0
#define timer4_IF_clear() TMR4IF = 0
#define timer4_IF_read() TMR4IF

// Other features
#define timer4_period_set(value) PR4 = value

/* -------------------------------------------------------------------------- */

// Setup
#define timer5_clock_source(value) T5CLK = value
#define timer5_prescale(value) T5CONbits.CKPS = value
#define timer5_clock_sync_enable() T5CONbits.NOT_SYNC = 0
#define timer5_clock_sync_disable() T5CONbits.NOT_SYNC = 1

// General manipulation
#define timer5_start() TMR5ON = 1
#define timer5_stop() TMR5ON = 0
#define timer5_clear()                                                         \
    do {                                                                       \
        TMR5H = 0x00;                                                          \
        TMR5L = 0x00;                                                          \
    } while (0)
#define timer5_read() (((uint16_t)TMR5H << 8) | (uint16_t)TMR5L)

// Interrupt control
#define timer5_interrupt_enable() TMR5IE = 1
#define timer5_interrupt_disable() TMR5IE = 0
#define timer5_IF_clear() TMR5IF = 0
#define timer5_IF_read() TMR5IF

// Other features
#define timer5_gate_enable() T5GE = 1
#define timer5_gate_disable() T5GE = 0

/* -------------------------------------------------------------------------- */

// Setup
#define timer6_clock_source(value) T6CLK = value
#define timer6_prescale(value) T6CONbits.CKPS = value
#define timer6_postscale(value) T6CONbits.OUTPS = value

// General manipulation
#define timer6_start() TMR6ON = 1
#define timer6_stop() TMR6ON = 0
#define timer6_clear() TMR6 = 0x00;
#define timer6_read() TMR6

// Interrupt control
#define timer6_interrupt_enable() TMR6IE = 1
#define timer6_interrupt_disable() TMR6IE = 0
#define timer6_IF_clear() TMR6IF = 0
#define timer6_IF_read() TMR6IF

// Other features
#define timer6_period_set(value) PR6 = value

/* ************************************************************************** */

enum timer_0_clock_source {
    TMR0_CLK_PPS = 0,
    TMR0_CLK_PPS_INVERTED = 1,
    TMR0_CLK_FOSC4 = 2,
    TMR0_CLK_HFINTOSC = 3,
    TMR0_CLK_LFINTOSC = 4,
    TMR0_CLK_MFINTOSC_500_K = 5,
    TMR0_CLK_SOSC = 6,
    TMR0_CLK_CLC1 = 7,
};

enum timer_1_clock_source {
    TMR1_CLK_CLC8 = 0b10101,
    TMR1_CLK_CLC7 = 0b10100,
    TMR1_CLK_CLC6 = 0b10011,
    TMR1_CLK_CLC5 = 0b10010,
    TMR1_CLK_CLC4 = 0b10001,
    TMR1_CLK_CLC3 = 0b10000,
    TMR1_CLK_CLC2 = 0b01111,
    TMR1_CLK_CLC1 = 0b01110,
    TMR1_CLK_TMR5 = 0b01101,
    TMR1_CLK_TMR3 = 0b01100,
    TMR1_CLK_TMR1 = 0b01011,
    TMR1_CLK_TMR0 = 0b01010,
    TMR1_CLK_CLKREF = 0b01001,
    TMR1_CLK_EXTOSC = 0b01000,
    TMR1_CLK_SOSC = 0b00111,
    TMR1_CLK_MFINTOSC_32_k = 0b00110,
    TMR1_CLK_MFINTOSC_500_k = 0b00101,
    TMR1_CLK_LFINTOSC = 0b00100,
    TMR1_CLK_HFINTOSC = 0b00011,
    TMR1_CLK_FOSC = 0b00010,
    TMR1_CLK_FOSC4 = 0b00001,
    TMR1_CLK_PPS = 0b00000,
};

enum timer_2_clock_source {
    TMR2_CLK_CLC8 = 0b10101,
    TMR2_CLK_CLC7 = 0b10100,
    TMR2_CLK_CLC6 = 0b10011,
    TMR2_CLK_CLC5 = 0b10010,
    TMR2_CLK_CLC4 = 0b10001,
    TMR2_CLK_CLC3 = 0b10000,
    TMR2_CLK_CLC2 = 0b01111,
    TMR2_CLK_CLC1 = 0b01110,
    TMR2_CLK_ZCD = 0b01101,
    TMR2_CLK_NCO3 = 0b01100,
    TMR2_CLK_NCO2 = 0b01011,
    TMR2_CLK_NCO1 = 0b01010,
    TMR2_CLK_CLKREF = 0b01001,
    TMR2_CLK_EXTOSC = 0b01000,
    TMR2_CLK_SOSC = 0b00111,
    TMR2_CLK_MFINTOSC_32_k = 0b00110,
    TMR2_CLK_MFINTOSC_500_k = 0b00101,
    TMR2_CLK_LFINTOSC = 0b00100,
    TMR2_CLK_HFINTOSC = 0b00011,
    TMR2_CLK_FOSC = 0b00010,
    TMR2_CLK_FOSC4 = 0b00001,
    TMR2_CLK_PPS = 0b00000,
};

// Timer 0 clock sources

/* -------------------------------------------------------------------------- */

// Shared timer prescale values
#define TMR_PRE_1_1 0
#define TMR_PRE_1_2 1
#define TMR_PRE_1_4 2
#define TMR_PRE_1_8 3
// Timer 0/2/4/6 prescale values
#define TMR_PRE_1_16 4
#define TMR_PRE_1_32 5
#define TMR_PRE_1_64 6
#define TMR_PRE_1_128 7
// Timer 0 prescale values
#define TMR_PRE_1_256 8
#define TMR_PRE_1_512 9
#define TMR_PRE_1_1024 10
#define TMR_PRE_1_2048 11
#define TMR_PRE_1_4096 12
#define TMR_PRE_1_8192 13
#define TMR_PRE_1_16384 14
#define TMR_PRE_1_32768 15

/* -------------------------------------------------------------------------- */

// Timer 0/2/4/6 postscale values
#define TMR_POST_1_1 0
#define TMR_POST_1_2 1
#define TMR_POST_1_3 2
#define TMR_POST_1_4 3
#define TMR_POST_1_5 4
#define TMR_POST_1_6 5
#define TMR_POST_1_7 6
#define TMR_POST_1_8 7
#define TMR_POST_1_9 8
#define TMR_POST_1_10 9
#define TMR_POST_1_11 10
#define TMR_POST_1_12 11
#define TMR_POST_1_13 12
#define TMR_POST_1_14 13
#define TMR_POST_1_15 14
#define TMR_POST_1_16 15

#endif