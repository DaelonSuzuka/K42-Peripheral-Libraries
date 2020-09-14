#include "adc.h"
#include "fixed_voltage_reference.h"
#include "pic_header.h"

/* ************************************************************************** */

void adc_init(void) {
    fvr_enable();

    ADREFbits.NREF = 0;    // Negative Voltage Reference, set to Vss
    ADREFbits.PREF = 0b11; // Positive Voltage Reference, set to FVR

    ADCON0bits.FM = 1; // adc result is right-justified

    ADCON0bits.CS = 0; // FOSC, divided by ADCLK
    ADCLK = 0b011111;  // FOSC/64

    ADCON0bits.ON = 1; // Enable ADC peripheral
}

/* -------------------------------------------------------------------------- */

//
#ifdef LATF
#define NUM_OF_CHANNELS 47 + 1
#elif defined LATD
#define NUM_OF_CHANNELS 34 + 1
#else
#define NUM_OF_CHANNELS 23 + 1
#endif

//
#define _1024mV FVR_GAIN_1X
#define _2048mV FVR_GAIN_2X
#define _4096mV FVR_GAIN_4X

// store the voltage setting per ADC channel
static uint8_t maxVoltage[NUM_OF_CHANNELS] = {
    _4096mV, // 0
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 5
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 10
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 15
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 20
    _4096mV, //
    _4096mV, //
    _4096mV, // 23

#ifdef LATD
    _4096mV, // 24

    _4096mV, // 25
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 30
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, // 34
#endif

#ifdef LATF
    _4096mV, // 35
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 40
    _4096mV, //
    _4096mV, //
    _4096mV, //
    _4096mV, //

    _4096mV, // 45
    _4096mV, //
    _4096mV, //
    _4096mV, // 48
#endif
};

#define adc_select_channel(channel) ADPCH = channel

//! Warning - input not sanitized
static void adc_select_scale(uint8_t scale) { fvr_set_adc_buffer_gain(scale); }

uint16_t adc_convert(uint8_t channel, uint8_t scale) {
    adc_select_channel(channel);
    adc_select_scale(scale);

    // Engage
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO) {
        // Wait for the conversion to finish
    }

    return ADRES;
}

/* -------------------------------------------------------------------------- */

uint16_t adc_read(uint8_t channel) {
    uint16_t measurement = 0;

    while (1) {
        adc_select_scale(maxVoltage[channel]);
        measurement = adc_convert(channel, maxVoltage[channel]);

        if (measurement < 1750) {
            if (maxVoltage[channel] > _1024mV) {
                maxVoltage[channel]--;
            } else {
                break;
            }
        } else if (measurement > 3900) {
            if (maxVoltage[channel] < _4096mV) {
                maxVoltage[channel]++;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    // Convert measurement to millivolts as needed.
    if (maxVoltage[channel] == _1024mV) {
        measurement /= 4;
    } else if (maxVoltage[channel] == _2048mV) {
        measurement /= 2;
    }

    return measurement;
}