#ifndef _NUMERICALLY_CONTROLLED_OSCILLATOR_H_
#define _NUMERICALLY_CONTROLLED_OSCILLATOR_H_

#include <stdint.h>

/* ************************************************************************** */

enum nco_pulse_width {
    NCO_PULSE_WIDTH_128 = 0b111,
    NCO_PULSE_WIDTH_64 = 0b110,
    NCO_PULSE_WIDTH_32 = 0b101,
    NCO_PULSE_WIDTH_16 = 0b100,
    NCO_PULSE_WIDTH_8 = 0b011,
    NCO_PULSE_WIDTH_4 = 0b010,
    NCO_PULSE_WIDTH_2 = 0b001,
    NCO_PULSE_WIDTH_1 = 0b000,
};

enum nco_clock_source {
    NCO_CLOCK_SOURCE_CLC4 = 0b1010,
    NCO_CLOCK_SOURCE_CLC3 = 0b1001,
    NCO_CLOCK_SOURCE_CLC2 = 0b1000,
    NCO_CLOCK_SOURCE_CLC1 = 0b0111,
    NCO_CLOCK_SOURCE_CLKREF = 0b0110,
    NCO_CLOCK_SOURCE_SOSC = 0b0101,
    NCO_CLOCK_SOURCE_MFINTOSC_32 = 0b0100,
    NCO_CLOCK_SOURCE_MFINTOSC_500 = 0b0011,
    NCO_CLOCK_SOURCE_LFINTOSC = 0b0010,
    NCO_CLOCK_SOURCE_HFINTOSC = 0b0001,
    NCO_CLOCK_SOURCE_FOSC = 0b0000,
};

enum nco_output_polarity {
    NCO_OUTPUT_INVERTED = 1,
    NCO_OUTPUT_NOT_INVERTED = 0,
};

enum nco_pulse_frequency_mode {
    NCO_MODE_PULSE_FREQUENCY = 1,
    NCO_MODE_FIXED_DUTY_CYCLE = 0,
};

/* ************************************************************************** */

//
extern void nco_set_clock_source(enum nco_clock_source source);

//
extern void nco_set_pulse_width(enum nco_pulse_width width);

//
extern void nco_set_output_polarity(enum nco_output_polarity polarity);

//
extern void nco_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode);

//
extern void nco_set_incrementor(uint24_t incrementor);

//
extern void nco_enable(void);

//
extern void nco_disable(void);

#endif /* _NUMERICALLY_CONTROLLED_OSCILLATOR_H_ */