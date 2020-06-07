#ifndef _CLC_H_
#define _CLC_H_

#include <stdint.h>

/* ************************************************************************** */
/*  CLC Data Input Selection

    These macros enumerate the possible selections for the CLC's Data Input,
    controlled by CLCxSEL0 through CLCxSEL3.
*/

#define CLC_CWG3B_OUT 0b110011
#define CLC_CWG3A_OUT 0b110010
#define CLC_CWG2B_OUT 0b110001
#define CLC_CWG2A_OUT 0b110000
#define CLC_CWG1B_OUT 0b101111
#define CLC_CWG1A_OUT 0b101110
#define CLC_SS1 0b101101
#define CLC_SCK1 0b101100
#define CLC_SDO1 0b101011
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

/* ************************************************************************** */

extern void clc1_passthrough_init(uint8_t dataInput);
extern void clc2_passthrough_init(uint8_t dataInput);
extern void clc3_passthrough_init(uint8_t dataInput);
extern void clc4_passthrough_init(uint8_t dataInput);

/* ************************************************************************** */

#endif