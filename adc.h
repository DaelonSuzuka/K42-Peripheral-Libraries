#ifndef _ADC_H_
#define _ADC_H_

#include <stdint.h>

/* ************************************************************************** */

// Setup and configuration
extern void adc_init(void);

// Actually measuring shit
extern uint16_t adc_read(uint8_t channel);

#endif