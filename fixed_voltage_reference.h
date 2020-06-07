#ifndef _FIXED_VOLTAGE_REFERENCE_H_
#define _FIXED_VOLTAGE_REFERENCE_H_

/* ************************************************************************** */
/*  Fixed Voltage Reference

    The PIC18FXXK42 family has a Fixed Voltage Reference peripheral that can be
    used as a reference voltage in several of its analog peripherals.

    FVR outputs can be used by the following peripherals:
    ADC input Channel
    ADC positive reference
    Comparator input
    Digital-to-Analog Converter
*/
/* ************************************************************************** */

// Turn the FVR module on or off
extern void fvr_enable(void);
extern void fvr_disable(void);

/* -------------------------------------------------------------------------- */

typedef enum {
    FVR_GAIN_OFF = 0b00, // Buffer is off
    FVR_GAIN_1X = 0b01,  // Buffer set to 1.024V
    FVR_GAIN_2X = 0b10,  // Buffer set to 2.048V
    FVR_GAIN_4X = 0b11,  // Buffer set to 4.096V
} fvr_gain_t;

// FVR Gain controls
extern void fvr_set_comparator_buffer_gain(fvr_gain_t gain);
extern void fvr_set_adc_buffer_gain(fvr_gain_t gain);

/* ************************************************************************** */
/*  Temperature Indicator Module

    The temperature indicator can -shockingly- measure the temperature inside
    the processor. The operating range of this module is -40C to +125C.

    The module converts temperature into an analog voltage that can be measured
    using the ADC peripheral. This output voltage is inversely proportional to
    the device temperature.

    The datasheet mentions improving the module's accuracy across the full
    operating range by way of "two-point or three-point calibration", but does
    not expand on the calibration process.

    The datasheet recommends taking multiple ADC measurements and averaging them
    to reduce noise and improve accuracy.

*/

extern void temp_indicator_enable(void);
extern void temp_indicator_disable(void);

/* -------------------------------------------------------------------------- */

typedef enum {
    LOW = 0b01,
    HIGH = 0b00,
} temp_range_t;

extern void temp_indicator_set_range(temp_range_t range);

#endif // _FIXED_VOLTAGE_REFERENCE_H_