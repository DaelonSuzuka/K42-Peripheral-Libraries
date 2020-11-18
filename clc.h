#ifndef _CLC_H_
#define _CLC_H_

#include "pic_family.h"
#include <stdint.h>

/* ************************************************************************** */
/*  CLC Data Input Selection

    These macros enumerate the possible selections for the CLC's Data Input,
    controlled by CLCxSEL0 through CLCxSEL3.
*/

#if FAMILY_Q43 || FAMILY_Q84

#define CLC_CLCIN0PPS 0b00000000
#define CLC_CLCIN1PPS 0b00000001
#define CLC_CLCIN2PPS 0b00000010
#define CLC_CLCIN3PPS 0b00000011
#define CLC_CLCIN4PPS 0b00000100
#define CLC_CLCIN5PPS 0b00000101
#define CLC_CLCIN6PPS 0b00000110
#define CLC_CLCIN7PPS 0b00000111
#define CLC_FOSC 0b00001000
#define CLC_HFINTOSC 0b00001001
#define CLC_LFINTOSC 0b00001010
#define CLC_MFINTOSC_500 0b00001011
#define CLC_MFINTOSC_31 0b00001100
#define CLC_SFINTOSC 0b00001101
#define CLC_SOSC 0b00001110
#define CLC_EXTOSC 0b00001111
#define CLC_ADCRC 0b00010000
#define CLC_CLKR 0b00010001
#define CLC_TMR0 0b00010010
#define CLC_TMR1 0b00010011
#define CLC_TMR2 0b00010100
#define CLC_TMR3 0b00010101
#define CLC_TMR4 0b00010110
#define CLC_TMR5 0b00010111
#define CLC_TMR6 0b00011000
#define CLC_SMT1 0b00011110
#define CLC_CCP1 0b00011111
#define CLC_CCP2 0b00100000
#define CLC_CCP3 0b00100001
#define CLC_PWM1S1P1_OUT 0b00100010
#define CLC_PWM1S1P2_OUT 0b00100011
#define CLC_PWM2S1P1_OUT 0b00100100
#define CLC_PWM2S1P2_OUT 0b00100101
#define CLC_PWM3S1P1_OUT 0b00100110
#define CLC_PWM3S1P2_OUT 0b00100111
#define CLC_NCO1 0b00101010
#define CLC_NCO2 0b00101011
#define CLC_NCO3 0b00101100
#define CLC_CMP1_OUT 0b00101101
#define CLC_CMP2_OUT 0b00101110
#define CLC_ZCD 0b00101111
#define CLC_IOC 0b00110000
#define CLC_DSM1 0b00110001
#define CLC_HLVD_OUT 0b00110010
#define CLC_CLC1 0b00110011
#define CLC_CLC2 0b00110100
#define CLC_CLC3 0b00110101
#define CLC_CLC4 0b00110110
#define CLC_CLC5 0b00110111
#define CLC_CLC6 0b00111000
#define CLC_CLC7 0b00111001
#define CLC_CLC8 0b00111010
#define CLC_U1TX 0b00111011
#define CLC_U2TX 0b00111100
#define CLC_U3TX 0b00111101
#define CLC_U4TX 0b00111110
#define CLC_U5TX 0b00111111
#define CLC_SPI1_SDO 0b01000000
#define CLC_SPI1_SCK 0b01000001
#define CLC_SPI1_SS 0b01000010
#define CLC_SPI2_SDO 0b01000011
#define CLC_SPI2_SCK 0b01000100
#define CLC_SPI2_SS 0b01000101
#define CLC_I2C_SCL 0b01000110
#define CLC_I2C_SDA 0b01000111
#define CLC_CWG1A 0b01001000
#define CLC_CWG1B 0b01001001
#define CLC_CWG2A 0b01001010
#define CLC_CWG2B 0b01001011
#define CLC_CWG3A 0b01001100
#define CLC_CWG3B 0b01001101

#else

#define CLC_CWG3B_OUT 0b110011
#define CLC_CWG3A_OUT 0b110010
#define CLC_CWG2B_OUT 0b110001
#define CLC_CWG2A_OUT 0b110000
#define CLC_CWG1B_OUT 0b101111
#define CLC_CWG1A_OUT 0b101110
#define CLC_SPI1_SS1 0b101101
#define CLC_SPI1_SCK1 0b101100
#define CLC_SPI1_SDO1 0b101011
#define CLC_UART2_TX_OUT 0b101001
#define CLC_UART1_TX_OUT 0b101000
#define CLC_CLC4_OUT 0b100111
#define CLC_CLC3_OUT 0b100110
#define CLC_CLC2_OUT 0b100101
#define CLC_CLC1_OUT 0b100100
#define CLC_DSM1_OUT 0b100011
#define CLC_IOC_FLAG 0b100010
#define CLC_ZCD_OUT 0b100001
#define CLC_CMP2_OUT 0b100000
#define CLC_CMP1_OUT 0b011111
#define CLC_NCO1_OUT 0b011110
#define CLC_PWM8_OUT 0b011011
#define CLC_PWM7_OUT 0b011010
#define CLC_PWM6_OUT 0b011001
#define CLC_PWM5_OUT 0b011000
#define CLC_CCP4_OUT 0b010111
#define CLC_CCP3_OUT 0b010110
#define CLC_CCP2_OUT 0b010101
#define CLC_CCP1_OUT 0b010100
#define CLC_SMT1_OUT 0b010011
#define CLC_TMR6_OUT 0b010010
#define CLC_TMR5_OVERFLOW 0b010001
#define CLC_TMR4_OUT 0b010000
#define CLC_TMR3_OVERFLOW 0b001111
#define CLC_TMR2_OUT 0b001110
#define CLC_TMR1_OVERFLOW 0b001101
#define CLC_TMR0_OVERFLOW 0b001100
#define CLC_CLKR_OUT 0b001011
#define CLC_ADCRC 0b001010
#define CLC_SOSC 0b001001
#define CLC_MFINTOSC_32 0b001000
#define CLC_MFINTOSC_500 0b000111
#define CLC_LFINTOSC 0b000110
#define CLC_HFINTOSC 0b000101
#define CLC_FOSC 0b000100
#define CLC_CLCIN3PPS 0b000011
#define CLC_CLCIN2PPS 0b000010
#define CLC_CLCIN1PPS 0b000001
#define CLC_CLCIN0PPS 0b000000

#endif

/* ************************************************************************** */

#if FAMILY_Q43 || FAMILY_Q84
extern void clc_passthrought_init(uint8_t clc_number, uint8_t dataInput);
#endif

extern void clc1_passthrough_init(uint8_t dataInput);
extern void clc2_passthrough_init(uint8_t dataInput);
extern void clc3_passthrough_init(uint8_t dataInput);
extern void clc4_passthrough_init(uint8_t dataInput);

/* ************************************************************************** */

#endif