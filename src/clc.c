#include "clc.h"
#include "pic_family.h"
#include "pic_header.h"

/* ************************************************************************** */

#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
void clc_passthrought_init(uint8_t clc_number, uint8_t dataInput) {
    CLCSELECT = clc_number;

    CLCnGLS0 = 0b00000010;
    CLCnGLS1 = 0b00001000;
    CLCnGLS2 = 0b00100000;
    CLCnGLS3 = 0b10000000;

    CLCnSEL0 = dataInput; // CLC1 data 0
    CLCnSEL1 = dataInput; // CLC1 data 1
    CLCnSEL2 = dataInput; // CLC1 data 2
    CLCnSEL3 = dataInput; // CLC1 data 3

    CLCnPOL = 0b00000000; // don't invert anything

    CLCnCONbits.MODE = 0b010; // 4-input AND mode

    CLCnCONbits.EN = 1; // turn it on
}
#endif

/* ************************************************************************** */

void clc1_passthrough_init(uint8_t dataInput) {
#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
    clc_passthrought_init(0, dataInput);
#else
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
#endif
}

/* -------------------------------------------------------------------------- */

void clc2_passthrough_init(uint8_t dataInput) {
#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
    clc_passthrought_init(1, dataInput);
#else
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
#endif
}

/* -------------------------------------------------------------------------- */

void clc3_passthrough_init(uint8_t dataInput) {
#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
    clc_passthrought_init(2, dataInput);
#else
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
#endif
}

/* -------------------------------------------------------------------------- */

void clc4_passthrough_init(uint8_t dataInput) {
#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
    clc_passthrought_init(3, dataInput);
#else
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
#endif
}