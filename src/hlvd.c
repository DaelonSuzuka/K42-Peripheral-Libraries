#include "hlvd.h"
#include "pic_header.h"

/* ************************************************************************** */

// Turn the HLVD module on or off
void hlvd_enable(void) { HLVDCON0bits.EN = 1; }
void hlvd_disable(void) { HLVDCON0bits.EN = 0; }

/* -------------------------------------------------------------------------- */

// Turn the HLVD interrupt source on or off
void hlvd_interrupt_enable(void) { PIE0bits.HLVDIE = 1; }
void hlvd_interrupt_disable(void) { PIE0bits.HLVDIE = 0; }

// Clear the HLVD interrupt flag
void hlvd_interrupt_clear(void) { PIR0bits.HLVDIF = 0; }

/* -------------------------------------------------------------------------- */

void hlvd_set_trigger_direction(trigger_direction_t direction) {
    switch (direction) {
    case OFF:
        HLVDCON0bits.INTH = 0;
        HLVDCON0bits.INTL = 0;
        break;
    case WHEN_ABOVE:
        HLVDCON0bits.INTH = 1;
        HLVDCON0bits.INTL = 0;
        break;
    case WHEN_BELOW:
        HLVDCON0bits.INTH = 0;
        HLVDCON0bits.INTL = 1;
        break;
    case BOTH:
        HLVDCON0bits.INTH = 1;
        HLVDCON0bits.INTL = 1;
        break;
    }
}

/* -------------------------------------------------------------------------- */

// This sets the HLVD trigger threshhold
void hlvd_set_trip_point(trip_point_t voltage) {
    HLVDCON1bits.SEL = voltage;
    
    // Wait for the HLVD threshold reference to stabilize before returning
    while (!HLVDCON0bits.RDY) {
        // intentionally empty loop
    };
}