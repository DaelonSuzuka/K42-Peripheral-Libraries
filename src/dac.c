#include "dac.h"
#include "pic_header.h"

/* ************************************************************************** */
/*  Raw DAC — 8-bit hardware output on RA0                                     */
/* ************************************************************************** */

void dac_init(void) {
    DAC1CONbits.OE = 1; // Output to RA0
    DAC1CONbits.EN = 1; // Enable DAC
}

void dac_write(uint8_t value) {
    DAC1DATL = value;
}

uint8_t dac_read(void) {
    return DAC1DATL;
}

/* ************************************************************************** */
/*  Virtual DAC — 12-bit Bresenham-dithered output                             */
/*                                                                            */
/*  12-bit value (0–4095) is split into integer (0–255) and fractional        */
/*  (0–15 substeps). Each call to vdac_service() writes the integer part      */
/*  to the hardware DAC, and adds the fraction to a 4-bit accumulator.        */
/*  On overflow, it writes integer+1 instead — spreading the +1 writes        */
/*  evenly across the period.                                                 */
/*                                                                            */
/*  Call vdac_service() from a Timer ISR at ~1 kHz.                           */
/* ************************************************************************** */

static volatile uint16_t vdac_value = 0;   // Current 12-bit target
static uint8_t vdac_accumulator = 0;         // 4-bit dither accumulator (0–15)

void vdac_init(void) {
    vdac_value = 0;
    vdac_accumulator = 0;
}

void vdac_write(uint16_t value) {
    if (value > VDAC_MAX)
        value = VDAC_MAX;
    vdac_value = value;
}

uint16_t vdac_read(void) {
    return vdac_value;
}

void vdac_service(void) {
    uint16_t val = vdac_value;         // Atomic read of 16-bit target
    uint8_t integer_part = val >> 4;   // 0–255
    uint8_t frac_part = val & 0x0F;    // 0–15

    vdac_accumulator += frac_part;
    if (vdac_accumulator >= 16) {
        // Fractional overflow — write integer+1 this tick
        DAC1DATL = (integer_part < 255) ? integer_part + 1 : 255;
        vdac_accumulator -= 16;
    } else {
        DAC1DATL = integer_part;
    }
}