#ifndef _NUMERICALLY_CONTROLLED_OSCILLATOR_H_
#define _NUMERICALLY_CONTROLLED_OSCILLATOR_H_

#include "pic_family.h"
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
#if FAMILY_K42
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
#elif FAMILY_Q43
    NCO_CLOCK_SOURCE_CLC8 = 0b11010,
    NCO_CLOCK_SOURCE_CLC7 = 0b11001,
    NCO_CLOCK_SOURCE_CLC6 = 0b11000,
    NCO_CLOCK_SOURCE_CLC5 = 0b10111,
    NCO_CLOCK_SOURCE_CLC4 = 0b10110,
    NCO_CLOCK_SOURCE_CLC3 = 0b10101,
    NCO_CLOCK_SOURCE_CLC2 = 0b10100,
    NCO_CLOCK_SOURCE_CLC1 = 0b10011,
    NCO_CLOCK_SOURCE_TU16B = 0b01100,
    NCO_CLOCK_SOURCE_TU16A = 0b01011,
    NCO_CLOCK_SOURCE_NCO3 = 0b10010, //!
    NCO_CLOCK_SOURCE_NCO2 = 0b10001, //!
    NCO_CLOCK_SOURCE_NCO1 = 0b10000, //!
    NCO_CLOCK_SOURCE_TMR6 = 0b01010,
    NCO_CLOCK_SOURCE_TMR4 = 0b01001,
    NCO_CLOCK_SOURCE_TMR2 = 0b01000,
    NCO_CLOCK_SOURCE_CLKREF = 0b00111,
    NCO_CLOCK_SOURCE_EXTOSC = 0b00110,
    NCO_CLOCK_SOURCE_SOSC = 0b00101,
    NCO_CLOCK_SOURCE_MFINTOSC_32 = 0b00100,
    NCO_CLOCK_SOURCE_MFINTOSC_500 = 0b00011,
    NCO_CLOCK_SOURCE_LFINTOSC = 0b00010,
    NCO_CLOCK_SOURCE_HFINTOSC = 0b00001,
#elif FAMILY_Q84
// not yet
#endif
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

// NCO1
extern void nco1_set_clock_source(enum nco_clock_source source);
extern void nco1_set_pulse_width(enum nco_pulse_width width);
extern void nco1_set_output_polarity(enum nco_output_polarity polarity);
extern void nco1_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode);
extern void nco1_set_incrementor(uint24_t incrementor);
extern void nco1_enable(void);
extern void nco1_disable(void);

/* -------------------------------------------------------------------------- */
//! Only available on Q43 and Q84 parts

// NCO2
extern void nco2_set_clock_source(enum nco_clock_source source);
extern void nco2_set_pulse_width(enum nco_pulse_width width);
extern void nco2_set_output_polarity(enum nco_output_polarity polarity);
extern void nco2_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode);
extern void nco2_set_incrementor(uint24_t incrementor);
extern void nco2_enable(void);
extern void nco2_disable(void);

// NCO3
extern void nco3_set_clock_source(enum nco_clock_source source);
extern void nco3_set_pulse_width(enum nco_pulse_width width);
extern void nco3_set_output_polarity(enum nco_output_polarity polarity);
extern void nco3_set_pulse_frequency_mode(enum nco_pulse_frequency_mode mode);
extern void nco3_set_incrementor(uint24_t incrementor);
extern void nco3_enable(void);
extern void nco3_disable(void);

#endif /* _NUMERICALLY_CONTROLLED_OSCILLATOR_H_ */