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
#define timer0_start() TIMER0_ON = 1
#define timer0_stop() TIMER0_ON = 0
#define timer0_clear()                                                         \
    do {                                                                       \
        TMR0H = 0x00;                                                          \
        TMR0L = 0x00;                                                          \
    } while (0)
#define timer0_read() (((uint16_t)TMR0H << 8) | (uint16_t)TMR0L)

// Interrupt control
#define timer0_interrupt_enable() TIMER0_IE = 1
#define timer0_interrupt_disable() TIMER0_IE = 0
#define timer0_IF_clear() TIMER0_IF = 0
#define timer0_IF_read() TIMER0_IF

// Other features
#define timer0_period_set(value) TMR0H = value // only in 8bit mode

/* -------------------------------------------------------------------------- */

// Setup
#define timer1_clock_source(value) T1CLK = value
#define timer1_prescale(value) T1CONbits.CKPS = value
#define timer1_clock_sync_enable() T1CONbits.NOT_SYNC = 0
#define timer1_clock_sync_disable() T1CONbits.NOT_SYNC = 1

// General manipulation
#define timer1_start() TIMER1_ON = 1
#define timer1_stop() TIMER1_ON = 0
#define timer1_clear()                                                         \
    do {                                                                       \
        TMR1H = 0x00;                                                          \
        TMR1L = 0x00;                                                          \
    } while (0)
#define timer1_read() (((uint16_t)TMR1H << 8) | (uint16_t)TMR1L)

// Interrupt control
#define timer1_interrupt_enable() TIMER1_IE = 1
#define timer1_interrupt_disable() TIMER1_IE = 0
#define timer1_IF_clear() TIMER1_IF = 0
#define timer1_IF_read() TIMER1_IF

// Other features
#define timer1_gate_enable() TIMER1_GATE_EN = 1
#define timer1_gate_disable() TIMER1_GATE_EN = 0

/* -------------------------------------------------------------------------- */

// Setup
#define timer2_clock_source(value) T2CLK = value
#define timer2_prescale(value) T2CONbits.CKPS = value
#define timer2_postscale(value) T2CONbits.OUTPS = value

// General manipulation
#define timer2_start() TIMER2_ON = 1
#define timer2_stop() TIMER2_ON = 0
#define timer2_clear() TMR2 = 0x00;
#define timer2_read() TMR2

// Interrupt control
#define timer2_interrupt_enable() TIMER2_IE = 1
#define timer2_interrupt_disable() TIMER2_IE = 0
#define timer2_IF_clear() TIMER2_IF = 0
#define timer2_IF_read() TIMER2_IF

// Other features
#define timer2_period_set(value) PR2 = value

/* -------------------------------------------------------------------------- */

// Setup
#define timer3_clock_source(value) T3CLK = value
#define timer3_prescale(value) T3CONbits.CKPS = value
#define timer3_clock_sync_enable() T3CONbits.NOT_SYNC = 0
#define timer3_clock_sync_disable() T3CONbits.NOT_SYNC = 1

// General manipulation
#define timer3_start() TIMER3_ON = 1
#define timer3_stop() TIMER3_ON = 0
#define timer3_clear()                                                         \
    do {                                                                       \
        TMR3H = 0x00;                                                          \
        TMR3L = 0x00;                                                          \
    } while (0)
#define timer3_read() (((uint16_t)TMR3H << 8) | (uint16_t)TMR3L)

// Interrupt control
#define timer3_interrupt_enable() TIMER3_IE = 1
#define timer3_interrupt_disable() TIMER3_IE = 0
#define timer3_IF_clear() TIMER3_IF = 0
#define timer3_IF_read() TIMER3_IF

// Other features
#define timer3_gate_enable() TIMER3_GATE_EN = 1
#define timer3_gate_disable() TIMER3_GATE_EN = 0

/* -------------------------------------------------------------------------- */

// Setup
#define timer4_clock_source(value) T4CLK = value
#define timer4_prescale(value) T4CONbits.CKPS = value
#define timer4_postscale(value) T4CONbits.OUTPS = value

// General manipulation
#define timer4_start() TIMER4_ON = 1
#define timer4_stop() TIMER4_ON = 0
#define timer4_clear() TMR4 = 0x00;
#define timer4_read() TMR4

// Interrupt control
#define timer4_interrupt_enable() TIMER4_IE = 1
#define timer4_interrupt_disable() TIMER4_IE = 0
#define timer4_IF_clear() TIMER4_IF = 0
#define timer4_IF_read() TIMER4_IF

// Other features
#define timer4_period_set(value) PR4 = value

/* -------------------------------------------------------------------------- */

// Setup
#define timer5_clock_source(value) T5CLK = value
#define timer5_prescale(value) T5CONbits.CKPS = value
#define timer5_clock_sync_enable() T5CONbits.NOT_SYNC = 0
#define timer5_clock_sync_disable() T5CONbits.NOT_SYNC = 1

// General manipulation
#define timer5_start() TIMER5_ON = 1
#define timer5_stop() TIMER5_ON = 0
#define timer5_clear()                                                         \
    do {                                                                       \
        TMR5H = 0x00;                                                          \
        TMR5L = 0x00;                                                          \
    } while (0)
#define timer5_read() (((uint16_t)TMR5H << 8) | (uint16_t)TMR5L)

// Interrupt control
#define timer5_interrupt_enable() TIMER5_IE = 1
#define timer5_interrupt_disable() TIMER5_IE = 0
#define timer5_IF_clear() TIMER5_IF = 0
#define timer5_IF_read() TIMER5_IF

// Other features
#define timer5_gate_enable() TIMER5_GATE_EN = 1
#define timer5_gate_disable() TIMER5_GATE_EN = 0

/* -------------------------------------------------------------------------- */

// Setup
#define timer6_clock_source(value) T6CLK = value
#define timer6_prescale(value) T6CONbits.CKPS = value
#define timer6_postscale(value) T6CONbits.OUTPS = value

// General manipulation
#define timer6_start() TIMER6_ON = 1
#define timer6_stop() TIMER6_ON = 0
#define timer6_clear() TMR6 = 0x00;
#define timer6_read() TMR6

// Interrupt control
#define timer6_interrupt_enable() TIMER6_IE = 1
#define timer6_interrupt_disable() TIMER6_IE = 0
#define timer6_IF_clear() TIMER6_IF = 0
#define timer6_IF_read() TIMER6_IF

// Other features
#define timer6_period_set(value) PR6 = value

/* ************************************************************************** */

// Timer X Interrupt Flag bit
#define TIMER0_IF PIR3bits.TMR0IF
#define TIMER1_IF PIR4bits.TMR1IF
#define TIMER2_IF PIR4bits.TMR2IF
#define TIMER3_IF PIR6bits.TMR3IF
#define TIMER4_IF PIR7bits.TMR4IF
#define TIMER5_IF PIR8bits.TMR5IF
#define TIMER6_IF PIR9bits.TMR6IF

// Timer X Interrupt Enable bit
#define TIMER0_IE PIE3bits.TMR0IE
#define TIMER1_IE PIE4bits.TMR1IE
#define TIMER2_IE PIE4bits.TMR2IE
#define TIMER3_IE PIE6bits.TMR3IE
#define TIMER4_IE PIE7bits.TMR4IE
#define TIMER5_IE PIE8bits.TMR5IE
#define TIMER6_IE PIE9bits.TMR6IE

// Timer X start bit
#define TIMER0_ON T0CON0bits.EN
#define TIMER1_ON T1CONbits.ON
#define TIMER2_ON T2CONbits.ON
#define TIMER3_ON T3CONbits.ON
#define TIMER4_ON T4CONbits.ON
#define TIMER5_ON T5CONbits.ON
#define TIMER6_ON T6CONbits.ON

// Timer 1/3/5 Gate Enable bit
#define TIMER1_GATE_EN T1GCONbits.GE
#define TIMER3_GATE_EN T3GCONbits.GE
#define TIMER5_GATE_EN T5GCONbits.GE

/* ************************************************************************** */

// Timer 1/2/3/4/5/6 clock sources - not comprehensive
#define TMR_CLK_PPS 0
#define TMR_CLK_FOSC4 1
#define TMR_CLK_FOSC 2
#define TMR_CLK_HFINTOSC 3
#define TMR_CLK_LFINTOSC 4
#define TMR_CLK_MFINTOSC_500_K 5
#define TMR_CLK_MFINTOSC_32_K 6
#define TMR_CLK_SOSC 7
#define TMR_CLK_CLKREF 8
#define TMR_CLK_CLC1 13
#define TMR_CLK_CLC2 14
#define TMR_CLK_CLC3 15
#define TMR_CLK_CLC4 16

// Timer 0 clock sources
#define TMR0_CLK_PPS 0
#define TMR0_CLK_PPS_INVERTED 1
#define TMR0_CLK_FOSC4 2
#define TMR0_CLK_HFINTOSC 3
#define TMR0_CLK_LFINTOSC 4
#define TMR0_CLK_MFINTOSC_500_K 5
#define TMR0_CLK_SOSC 6
#define TMR0_CLK_CLC1 7

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