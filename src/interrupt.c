#include "interrupt.h"
#include "pic_header.h"

/* ************************************************************************** */

void begin_critical_section(void) { INTCON0bits.GIE = 0; }
void end_critical_section(void) { INTCON0bits.GIE = 1; }

/* ************************************************************************** */

void interrupt_init(void) {
    INTCON0bits.IPEN = 0; // Disable priority levels on interrupts

    // Clear all peripheral interrupts
    PIE1 = 0x0;
    PIE2 = 0x0;
    PIE3 = 0x0;
    PIE4 = 0x0;
    PIE5 = 0x0;
    PIE6 = 0x0;
    PIE7 = 0x0;
    PIE8 = 0x0;
    PIE9 = 0x0;

    INTCON0bits.GIE = 1;
}

// Providing this function prevents the compiler from complaining about
// "unused reset vectors"
void __interrupt(irq(default), high_priority) default_ISR(void) {
    //
}