#include "adc.h"
#include "fixed_voltage_reference.h"
#include "os/logging.h"
#include "pic_header.h"
static uint8_t LOG_LEVEL = L_SILENT;

/* ************************************************************************** */

#define ADREF_NREF_EXT 1
#define ADREF_NREF_VSS 0

#define ADREF_PREF_FVR 0b11
#define ADREF_PREF_EXT 0b10
#define ADREF_PREF_VDD 0b00

void adc_init(void) {
    fvr_enable();

    ADREFbits.NREF = ADREF_NREF_VSS;
    ADREFbits.PREF = ADREF_PREF_VDD;

    ADCON0bits.FM = 1; // adc result is right-justified

    ADCON0bits.CS = 0; // FOSC, divided by ADCLK
    ADCLK = 0b011111;  // FOSC/64

    ADCON0bits.ON = 1; // Enable ADC peripheral

    log_register();
}

/* -------------------------------------------------------------------------- */

//
#ifdef LATF
#define NUM_OF_CHANNELS 48 + 1
#elif defined LATD
#define NUM_OF_CHANNELS 34 + 1
#else
#define NUM_OF_CHANNELS 23 + 1
#endif

typedef enum {
    _1024mV = FVR_GAIN_1X,
    _2048mV = FVR_GAIN_2X,
    _4096mV = FVR_GAIN_4X,
    _5000mV,
} adc_scale_settings_t;

//
// #define _1024mV FVR_GAIN_1X
// #define _2048mV FVR_GAIN_2X
// #define _4096mV FVR_GAIN_4X
// #define _5000mV VCC

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
static void adc_select_scale(uint8_t scale) {
    if (scale < _5000mV) {
        ADREFbits.PREF = ADREF_PREF_FVR;
        fvr_set_adc_buffer_gain(scale);
    } else {
        ADREFbits.PREF = ADREF_PREF_VDD;
    }
}

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

uint16_t convert_to_millivolts(uint16_t measurement, uint8_t scale) {
    if (scale == _1024mV) {
        measurement /= 4;
    } else if (scale == _2048mV) {
        measurement /= 2;
    } else if (scale == _5000mV) {
        float temp = (float)measurement * 1.22;
        measurement = (uint16_t)temp;
    }
    return measurement;
}

uint16_t adc_read(uint8_t channel) {
    LOG_TRACE({ println("adc_read"); });

    uint16_t measurement = 0;

    while (1) {
        measurement = adc_convert(channel, maxVoltage[channel]);

        LOG_DEBUG({
            printf("channel: %d, ", channel);
            printf("maxVoltage: %d, ", maxVoltage[channel]);
            printf("raw: %u, ",  measurement);
            printf("adjusted: %u",  convert_to_millivolts(measurement, maxVoltage[channel]));
            println("");
        });

        if (measurement < 1750) {
            if (maxVoltage[channel] > _1024mV) {
                // LOG_INFO({ printf("ch: %d, V+\r\n", channel); });
                maxVoltage[channel]--;
            } else {
                break;
            }
        } else if (measurement > 3900) {
            if (maxVoltage[channel] < _5000mV) {
                // LOG_INFO({ printf("ch: %d, V-\r\n", channel); });
                maxVoltage[channel]++;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    return convert_to_millivolts(measurement, maxVoltage[channel]);
}