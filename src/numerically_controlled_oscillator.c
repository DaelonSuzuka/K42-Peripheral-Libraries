#include "numerically_controlled_oscillator.h"
#include "pic_header.h"

/* ************************************************************************** */

void nco_set_clock_source(enum nco_clock_source source) {
    //
    NCO1CLKbits.CKS = source;
}

void nco_set_pulse_width(enum nco_pulse_width width) {
    //
    NCO1CLKbits.PWS = width;
}

void nco_set_output_polarity(enum nco_output_polarity polarity) {
    //
    NCO1CONbits.POL = polarity;
}

void nco_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode) {
    //
    NCO1CONbits.PFM = mode;
}

void nco_set_incrementor(uint24_t incrementor) {
    //
    NCO1INC = incrementor;
}

void nco_enable(void) {
    //
    NCO1CONbits.EN = 1;
}

void nco_disable(void) {
    //
    NCO1CONbits.EN = 0;
}
