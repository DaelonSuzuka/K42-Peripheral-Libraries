#ifndef _SIGNAL_MEASUREMENT_TIMER_H_
#define _SIGNAL_MEASUREMENT_TIMER_H_

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