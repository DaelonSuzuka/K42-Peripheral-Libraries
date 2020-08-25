#include "signal_measurement_timer.h"
#include "pic_header.h"

/* ************************************************************************** */

//
void smt_enable(void) { SMT1CON0bits.EN = 1; }
void smt_disable(void) { SMT1CON0bits.EN = 0; }

//
void smt_start(void) { SMT1CON1bits.GO = 1; }
void smt_stop(void) { SMT1CON1bits.GO = 0; }

void smt_clear(void) { SMT1TMR = 0; }
void smt_latch_now(void) { SMT1STATbits.CPRUP = 1; }
uint24_t smt_read(void) { return SMT1CPR; }

//
void smt_interrupt_enable(void) { PIE1bits.SMT1IE = 1; }
void smt_interrupt_disable(void) { PIE1bits.SMT1IE = 0; }
void smt_clear_interrupt_flag(void) { PIR1bits.SMT1IF = 0; }

//
void smt_set_clock_source(enum smt_clock_selection clock) {
    SMT1CLKbits.CSEL = clock;
}

//
void smt_set_window_input(enum smt_window_input window) {
    SMT1WINbits.WSEL = window;
}

//
void smt_set_signal_input(enum smt_signal_input signal) {
    SMT1SIGbits.SSEL = signal;
}

//
void smt_set_prescale(enum smt_prescale_select prescale) {
    SMT1CON0bits.PS = prescale;
}

//
void smt_set_operation_mode(enum smt_operation_mode mode) {
    SMT1CON1bits.MODE = mode;
}