#ifndef _ADC_H_
#define _ADC_H_

#include "fixed_voltage_reference.h"
#include <stdint.h>

/* ************************************************************************** */

typedef enum {
    _1024mV = FVR_GAIN_1X,
    _2048mV = FVR_GAIN_2X,
    _4096mV = FVR_GAIN_4X,
    _5000mV,
} adc_scale_t;

/* -------------------------------------------------------------------------- */

// Setup and configuration
extern void adc_init(void);

// Measure the specified channel using a fixed scale, returning the raw result
extern uint16_t adc_convert(uint8_t channel, adc_scale_t scale);

// Convert a measurement to mV, using to a given scale
extern uint16_t convert_to_millivolts(uint16_t measurement, adc_scale_t scale);

// Measure the specified channel using the auto-scale mechanism
// Result is converted to mV according the detected scale
extern uint16_t adc_read(uint8_t channel);

#endif /* _ADC_H_ */