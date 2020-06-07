#include "clc.h"
#include "pic_header.h"

/* ************************************************************************** */

void clc1_passthrough_init(uint8_t dataInput) {
    CLC1GLS0 = 0b00000010;
    CLC1GLS1 = 0b00001000;
    CLC1GLS2 = 0b00100000;
    CLC1GLS3 = 0b10000000;

    CLC1SEL0 = dataInput; // CLC1 data 0
    CLC1SEL1 = dataInput; // CLC1 data 1
    CLC1SEL2 = dataInput; // CLC1 data 2
    CLC1SEL3 = dataInput; // CLC1 data 3

    CLC1POL = 0b00000000; // don't invert anything

    CLC1CONbits.MODE = 0b010; // 4-input AND mode

    CLC1CONbits.EN = 1; // turn it on
}

/* -------------------------------------------------------------------------- */

void clc2_passthrough_init(uint8_t dataInput) {
    CLC2GLS0 = 0b00000010;
    CLC2GLS1 = 0b00001000;
    CLC2GLS2 = 0b00100000;
    CLC2GLS3 = 0b10000000;

    CLC2SEL0 = dataInput; // CLC1 data 0
    CLC2SEL1 = dataInput; // CLC1 data 1
    CLC2SEL2 = dataInput; // CLC1 data 2
    CLC2SEL3 = dataInput; // CLC1 data 3

    CLC2POL = 0b00000000; // don't invert anything

    CLC2CONbits.MODE = 0b010; // 4-input AND mode

    CLC2CONbits.EN = 1; // turn it on
}

/* -------------------------------------------------------------------------- */

void clc3_passthrough_init(uint8_t dataInput) {
    CLC3GLS0 = 0b00000010;
    CLC3GLS1 = 0b00001000;
    CLC3GLS2 = 0b00100000;
    CLC3GLS3 = 0b10000000;

    CLC3SEL0 = dataInput; // CLC1 data 0
    CLC3SEL1 = dataInput; // CLC1 data 1
    CLC3SEL2 = dataInput; // CLC1 data 2
    CLC3SEL3 = dataInput; // CLC1 data 3

    CLC3POL = 0b00000000; // don't invert anything

    CLC3CONbits.MODE = 0b010; // 4-input AND mode

    CLC3CONbits.EN = 1; // turn it on
}

/* -------------------------------------------------------------------------- */

void clc4_passthrough_init(uint8_t dataInput) {
    CLC4GLS0 = 0b00000010;
    CLC4GLS1 = 0b00001000;
    CLC4GLS2 = 0b00100000;
    CLC4GLS3 = 0b10000000;

    CLC4SEL0 = dataInput; // CLC1 data 0
    CLC4SEL1 = dataInput; // CLC1 data 1
    CLC4SEL2 = dataInput; // CLC1 data 2
    CLC4SEL3 = dataInput; // CLC1 data 3

    CLC4POL = 0b00000000; // don't invert anything

    CLC4CONbits.MODE = 0b010; // 4-input AND mode

    CLC4CONbits.EN = 1; // turn it on
}