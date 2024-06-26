#ifndef _SIGNAL_MEASUREMENT_TIMER_H_
#define _SIGNAL_MEASUREMENT_TIMER_H_

#include "pic_family.h"
#include <stdint.h>

/* ************************************************************************** */

enum smt_clock_selection {
    SMT_CLOCK_SELECTION_CLKREF = 0b111,
    SMT_CLOCK_SELECTION_SOSC = 0b110,
    SMT_CLOCK_SELECTION_MFINTOSC_32 = 0b101,
    SMT_CLOCK_SELECTION_MFINTOSC_500 = 0b100,
    SMT_CLOCK_SELECTION_LFINTOSC = 0b011,
    SMT_CLOCK_SELECTION_HFINTOSC = 0b010,
    SMT_CLOCK_SELECTION_FOSC = 0b001,
    SMT_CLOCK_SELECTION_FOSC_4 = 0b000,
};

enum smt_window_input {
    SMT_WINDOW_INPUT_CLC4 = 0b11010,
    SMT_WINDOW_INPUT_CLC3 = 0b11001,
    SMT_WINDOW_INPUT_CLC2 = 0b11000,
    SMT_WINDOW_INPUT_CLC1 = 0b10111,
    SMT_WINDOW_INPUT_ZCD1 = 0b10110,
    SMT_WINDOW_INPUT_CMP2 = 0b10101,
    SMT_WINDOW_INPUT_CMP1 = 0b10100,
    SMT_WINDOW_INPUT_NCO1 = 0b10011,
    SMT_WINDOW_INPUT_PWM8 = 0b10000,
    SMT_WINDOW_INPUT_PWM7 = 0b01111,
    SMT_WINDOW_INPUT_PWM6 = 0b01110,
    SMT_WINDOW_INPUT_PWM5 = 0b01101,
    SMT_WINDOW_INPUT_CCP4 = 0b01100,
    SMT_WINDOW_INPUT_CCP3 = 0b01011,
    SMT_WINDOW_INPUT_CCP2 = 0b01010,
    SMT_WINDOW_INPUT_CCP1 = 0b01001,
    SMT_WINDOW_INPUT_TMR6 = 0b01000,
    SMT_WINDOW_INPUT_TMR4 = 0b00111,
    SMT_WINDOW_INPUT_TMR2 = 0b00110,
    SMT_WINDOW_INPUT_CLKREF = 0b00100,
    SMT_WINDOW_INPUT_SOSC = 0b00011,
    SMT_WINDOW_INPUT_MFINTOSC_32 = 0b00010,
    SMT_WINDOW_INPUT_LFINTOSC = 0b00001,
    SMT_WINDOW_INPUT_SMTxWINPPS = 0b00000,
};

enum smt_signal_input {
#if FAMILY_Q43
    SMT_SIGNAL_INPUT_CLC8 = 0b100101,
    SMT_SIGNAL_INPUT_CLC7 = 0b100100,
    SMT_SIGNAL_INPUT_CCP1 = 0b001101,
    SMT_SIGNAL_INPUT_CCP3 = 0b001111,
    SMT_SIGNAL_INPUT_PWM1S1P1 = 0b010000,
    SMT_SIGNAL_INPUT_PWM2S1P1 = 0b010010,
    SMT_SIGNAL_INPUT_PWM2S1P2 = 0b010011,
    SMT_SIGNAL_INPUT_PWM3S1P1 = 0b010100,
    SMT_SIGNAL_INPUT_PWM3S1P2 = 0b010101,
    SMT_SIGNAL_INPUT_NCO1 = 0b011000,
    SMT_SIGNAL_INPUT_NCO2 = 0b011001,
    SMT_SIGNAL_INPUT_NCO3 = 0b011010,
    SMT_SIGNAL_INPUT_CMP1 = 0b011011,
    SMT_SIGNAL_INPUT_CMP2 = 0b011100,
    SMT_SIGNAL_INPUT_ZCD = 0b011101,
    SMT_SIGNAL_INPUT_CLC1 = 0b011110,
    SMT_SIGNAL_INPUT_CLC2 = 0b011111,
    SMT_SIGNAL_INPUT_CLC3 = 0b100000,
    SMT_SIGNAL_INPUT_CLC5 = 0b100010,
    SMT_SIGNAL_INPUT_CLC4 = 0b100001,
    SMT_SIGNAL_INPUT_CLC6 = 0b100011,
    SMT_SIGNAL_INPUT_CCP2 = 0b001110,
    SMT_SIGNAL_INPUT_PWM1S1P2 = 0b010001,
    SMT_SIGNAL_INPUT_TMR6_Postscaler = 0b000111,
    SMT_SIGNAL_INPUT_TMR5 = 0b000110,
    SMT_SIGNAL_INPUT_TMR4_Postscaler = 0b000101,
    SMT_SIGNAL_INPUT_TMR3 = 0b000100,
    SMT_SIGNAL_INPUT_TMR2_Postscaler = 0b000011,
    SMT_SIGNAL_INPUT_TMR1 = 0b000010,
    SMT_SIGNAL_INPUT_TMR0 = 0b000001,
    SMT_SIGNAL_INPUT_SMT1SIGPPS = 0b000000,
#elif FAMILY_K42
    SMT_SIGNAL_INPUT_CLC4 = 0b11001,
    SMT_SIGNAL_INPUT_CLC3 = 0b11000,
    SMT_SIGNAL_INPUT_CLC2 = 0b10111,
    SMT_SIGNAL_INPUT_CLC1 = 0b10110,
    SMT_SIGNAL_INPUT_ZCD1 = 0b10101,
    SMT_SIGNAL_INPUT_CMP2 = 0b10100,
    SMT_SIGNAL_INPUT_CMP1 = 0b10011,
    SMT_SIGNAL_INPUT_NCO1 = 0b10010,
    SMT_SIGNAL_INPUT_PWM8 = 0b01111,
    SMT_SIGNAL_INPUT_PWM7 = 0b01110,
    SMT_SIGNAL_INPUT_PWM6 = 0b01101,
    SMT_SIGNAL_INPUT_PWM5 = 0b01100,
    SMT_SIGNAL_INPUT_CCP4 = 0b01011,
    SMT_SIGNAL_INPUT_CCP3 = 0b01010,
    SMT_SIGNAL_INPUT_CCP2 = 0b01001,
    SMT_SIGNAL_INPUT_CCP1 = 0b01000,
    SMT_SIGNAL_INPUT_TMR6 = 0b00111,
    SMT_SIGNAL_INPUT_TMR5 = 0b00110,
    SMT_SIGNAL_INPUT_TMR4 = 0b00101,
    SMT_SIGNAL_INPUT_TMR3 = 0b00100,
    SMT_SIGNAL_INPUT_TMR2 = 0b00011,
    SMT_SIGNAL_INPUT_TMR1 = 0b00010,
    SMT_SIGNAL_INPUT_TMR0 = 0b00001,
    SMT_SIGNAL_INPUT_SMTxSIGPPS = 0b00000,
#elif FAMILY_Q41
    SMT_SIGNAL_INPUT_CLC4 = 0b10100,
    SMT_SIGNAL_INPUT_CLC3 = 0b10011,
    SMT_SIGNAL_INPUT_CLC2 = 0b10010,
    SMT_SIGNAL_INPUT_CLC1 = 0b10001,
    SMT_SIGNAL_INPUT_ZCD = 0b10000,
    SMT_SIGNAL_INPUT_CMP2 = 0b01111,
    SMT_SIGNAL_INPUT_CMP1 = 0b01110,
    SMT_SIGNAL_INPUT_NCO1 = 0b01101,
    SMT_SIGNAL_INPUT_PWM3S1P2 = 0b01100,
    SMT_SIGNAL_INPUT_PWM3S1P1 = 0b01011,
    SMT_SIGNAL_INPUT_PWM2S1P2 = 0b01010,
    SMT_SIGNAL_INPUT_PWM2S1P1 = 0b01001,
    SMT_SIGNAL_INPUT_PWM1S1P2 = 0b01000,
    SMT_SIGNAL_INPUT_PWM1S1P1 = 0b00111,
    SMT_SIGNAL_INPUT_CCP1 = 0b00110,
    SMT_SIGNAL_INPUT_TMR4 = 0b00101,
    SMT_SIGNAL_INPUT_TMR3 = 0b00100,
    SMT_SIGNAL_INPUT_TMR2 = 0b00011,
    SMT_SIGNAL_INPUT_TMR1 = 0b00010,
    SMT_SIGNAL_INPUT_TMR0 = 0b00001,
    SMT_SIGNAL_INPUT_SMT1SIGPPS = 0b00000,
#endif
};

enum smt_prescale_select {
    SMT_PRESCALE_1_8 = 0b11,
    SMT_PRESCALE_1_4 = 0b10,
    SMT_PRESCALE_1_2 = 0b01,
    SMT_PRESCALE_1_1 = 0b00,
};

enum smt_operation_mode {
    SMT_MODE_WINDOWED_COUNTER = 0b1010,
    SMT_MODE_GATED_COUNTER = 0b1001,
    SMT_MODE_COUNTER = 0b1000,
    SMT_MODE_CAPTURE = 0b0111,
    SMT_MODE_TIME_OF_FLIGHT = 0b0110,
    SMT_MODE_GATED_WINDOWED_MEASURE = 0b0101,
    SMT_MODE_WINDOWED_MEASURE = 0b0100,
    SMT_MODE_HIGH_LOW_TIME_MEASUREMENT = 0b0011,
    SMT_MODE_PERIOD_DUTY_CYCLE_ACQUISITION = 0b0010,
    SMT_MODE_GATED_TIMER = 0b0001,
    SMT_MODE_TIMER = 0b0000,
};

/* ************************************************************************** */

//
extern void smt_enable(void);
extern void smt_disable(void);

//
extern void smt_start(void);
extern void smt_stop(void);

extern void smt_clear(void);
extern void smt_latch_now(void);
extern uint24_t smt_read(void);

//
extern void smt_interrupt_enable(void);
extern void smt_interrupt_disable(void);
extern void smt_clear_interrupt_flag(void);

//
extern void smt_set_clock_source(enum smt_clock_selection clock);
extern void smt_set_window_input(enum smt_window_input window);
extern void smt_set_signal_input(enum smt_signal_input signal);
extern void smt_set_prescale(enum smt_prescale_select prescale);
extern void smt_set_operation_mode(enum smt_operation_mode mode);

#endif /* _SIGNAL_MEASUREMENT_TIMER_H_ */