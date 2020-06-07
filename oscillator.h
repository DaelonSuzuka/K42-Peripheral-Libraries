#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_

/* ************************************************************************** */

typedef enum {
    _64_Mhz = 0b1000,
    _48_Mhz = 0b0111,
    _32_Mhz = 0b0110,
    _16_Mhz = 0b0101,
    _12_Mhz = 0b0100,
    _8_Mhz = 0b0011,
    _4_Mhz = 0b0010,
    _2_Mhz = 0b0001,
    _1_Mhz = 0b0000,
} HFINTOSC_freq_t;

typedef enum {
    EXTOSC = 0b111,
    HFINTOSC = 0b110,
    LFINTOSC = 0b101,
    SOSC = 0b100,
    EXTOSC_4x_PLL = 0b010,
} clock_source_t;

typedef enum {
    _by_512 = 0b1001,
    _by_256 = 0b1000,
    _by_128 = 0b0111,
    _by_64 = 0b0110,
    _by_32 = 0b0101,
    _by_16 = 0b0100,
    _by_8 = 0b0011,
    _by_4 = 0b0010,
    _by_2 = 0b0001,
    _by_1 = 0b0000,
} clock_divider_t;

typedef struct {
    HFINTOSC_freq_t freq;
    clock_source_t source;
    clock_divider_t divider;
} osc_settings_t;

// init the system oscillator according to the provided specs
extern void oscillator_init(osc_settings_t settings);

/* ************************************************************************** */

// Set up the external oscillator
extern void external_oscillator_init(void);

// Set up the internal oscillator(HFINTOSC)
extern void internal_oscillator_init(void);

#endif