#include "fixed_voltage_reference.h"
#include "pic_header.h"

/* ************************************************************************** */

void fvr_enable(void) { FVRCONbits.EN = 1; }
void fvr_disable(void) { FVRCONbits.EN = 0; }

/* -------------------------------------------------------------------------- */

// FVR Gain controls
void fvr_set_comparator_buffer_gain(fvr_gain_t gain) {
    FVRCONbits.CDAFVR = gain;

    // Wait for the FVR output to stabilize before returning
    while (!FVRCONbits.RDY) {
        // intentionally empty loop
    };
}

void fvr_set_adc_buffer_gain(fvr_gain_t gain) {
    FVRCONbits.ADFVR = gain;

    // Wait for the FVR output to stabilize before returning
    while (!FVRCONbits.RDY) {
        // intentionally empty loop
    };
}

/* ************************************************************************** */

void temp_indicator_enable(void) { FVRCONbits.TSEN = 1; }
void temp_indicator_disable(void) { FVRCONbits.TSEN = 0; }

/* -------------------------------------------------------------------------- */

void temp_indicator_set_range(temp_range_t range) { FVRCONbits.TSRNG = range; }