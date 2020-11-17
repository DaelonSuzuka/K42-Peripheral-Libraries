#include "numerically_controlled_oscillator.h"
#include "pic_header.h"

/* ************************************************************************** */

void nco1_set_clock_source(enum nco_clock_source source) {
    //
    NCO1CLKbits.CKS = source;
}

void nco1_set_pulse_width(enum nco_pulse_width width) {
    //
    NCO1CLKbits.PWS = width;
}

void nco1_set_output_polarity(enum nco_output_polarity polarity) {
    //
    NCO1CONbits.POL = polarity;
}

void nco1_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode) {
    //
    NCO1CONbits.PFM = mode;
}

void nco1_set_incrementor(uint24_t incrementor) {
    //
    NCO1INC = incrementor;
}

void nco1_enable(void) {
    //
    NCO1CONbits.EN = 1;
}

void nco1_disable(void) {
    //
    NCO1CONbits.EN = 0;
}

/* -------------------------------------------------------------------------- */
#if FAMILY_Q43 || FAMILY_Q84

void nco2_set_clock_source(enum nco_clock_source source) {
    //
    NCO2CLKbits.CKS = source;
}

void nco2_set_pulse_width(enum nco_pulse_width width) {
    //
    NCO2CLKbits.PWS = width;
}

void nco2_set_output_polarity(enum nco_output_polarity polarity) {
    //
    NCO2CONbits.POL = polarity;
}

void nco2_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode) {
    //
    NCO2CONbits.PFM = mode;
}

void nco2_set_incrementor(uint24_t incrementor) {
    //
    NCO2INC = incrementor;
}

void nco2_enable(void) {
    //
    NCO2CONbits.EN = 1;
}

void nco2_disable(void) {
    //
    NCO2CONbits.EN = 0;
}

/* -------------------------------------------------------------------------- */

void nco3_set_clock_source(enum nco_clock_source source) {
    //
    NCO3CLKbits.CKS = source;
}

void nco3_set_pulse_width(enum nco_pulse_width width) {
    //
    NCO3CLKbits.PWS = width;
}

void nco3_set_output_polarity(enum nco_output_polarity polarity) {
    //
    NCO3CONbits.POL = polarity;
}

void nco3_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode) {
    //
    NCO3CONbits.PFM = mode;
}

void nco3_set_incrementor(uint24_t incrementor) {
    //
    NCO3INC = incrementor;
}

void nco3_enable(void) {
    //
    NCO3CONbits.EN = 1;
}

void nco3_disable(void) {
    //
    NCO3CONbits.EN = 0;
}

#endif