#ifndef _TIMER_CONSTANTS_H_
#define _TIMER_CONSTANTS_H_

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

/* -------------------------------------------------------------------------- */

enum timer_prescale {
    TMR_PRESCALE_1 = 0,
    TMR_PRESCALE_2 = 1,
    TMR_PRESCALE_4 = 2,
    TMR_PRESCALE_8 = 3,
    TMR_PRESCALE_16 = 4,
    TMR_PRESCALE_32 = 5,
    TMR_PRESCALE_64 = 6,
    TMR_PRESCALE_128 = 7,
    TMR_PRESCALE_256 = 8,
    TMR_PRESCALE_512 = 9,
    TMR_PRESCALE_1024 = 10,
    TMR_PRESCALE_2048 = 11,
    TMR_PRESCALE_4096 = 12,
    TMR_PRESCALE_8192 = 13,
    TMR_PRESCALE_16384 = 14,
    TMR_PRESCALE_32768 = 15,
};

enum timer_postscale {
    TMR_POSTSCALE_1 = 0,
    TMR_POSTSCALE_2 = 1,
    TMR_POSTSCALE_3 = 2,
    TMR_POSTSCALE_4 = 3,
    TMR_POSTSCALE_5 = 4,
    TMR_POSTSCALE_6 = 5,
    TMR_POSTSCALE_7 = 6,
    TMR_POSTSCALE_8 = 7,
    TMR_POSTSCALE_9 = 8,
    TMR_POSTSCALE_10 = 9,
    TMR_POSTSCALE_11 = 10,
    TMR_POSTSCALE_12 = 11,
    TMR_POSTSCALE_13 = 12,
    TMR_POSTSCALE_14 = 13,
    TMR_POSTSCALE_15 = 14,
    TMR_POSTSCALE_16 = 15,
};


/* ************************************************************************** */
// old style, left for compatibility

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

#endif // _TIMER_CONSTANTS_H_