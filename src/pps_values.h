#ifndef _PPS_VALUES_H_
#define _PPS_VALUES_H_

#include "pic_family.h"

/* ************************************************************************** */
// K42 output values

#if FAMILY_K42

// K42 output values
#define PPS_ADGRDB 0b110010
#define PPS_ADGRDA 0b110001
#define PPS_CWG3D 0b110000
#define PPS_CWG3C 0b101111
#define PPS_CWG3B 0b101110
#define PPS_CWG3A 0b101101
#define PPS_CWG2D 0b101100
#define PPS_CWG2C 0b101011
#define PPS_CWG2B 0b101010
#define PPS_CWG2A 0b101001
#define PPS_DSM1 0b101000
#define PPS_CLKR 0b100111
#define PPS_NCO1 0b100110
#define PPS_TMR0 0b100101
#define PPS_I2C2_SDA 0b100100
#define PPS_I2C2_SCL 0b100011
#define PPS_I2C1_SDA 0b100010
#define PPS_I2C1_SCL 0b100001
#define PPS_SPI1_SS 0b100000
#define PPS_SPI1_SDO 0b011111
#define PPS_SPI1_SCK 0b011110
#define PPS_C2OUT 0b011101
#define PPS_C1OUT 0b011100
#define PPS_UART2_RTS 0b011000
#define PPS_UART2_TXDE 0b010111
#define PPS_UART2_TX 0b010110
#define PPS_UART1_RTS 0b010101
#define PPS_UART1_TXDE 0b010100
#define PPS_UART1_TX 0b010011
#define PPS_PWM8 0b010000
#define PPS_PWM7 0b001111
#define PPS_PWM6 0b001110
#define PPS_PWM5 0b001101
#define PPS_CCP4 0b001100
#define PPS_CCP3 0b001100
#define PPS_CCP2 0b001010
#define PPS_CCP1 0b001001
#define PPS_CWG1D 0b001000
#define PPS_CWG1C 0b000111
#define PPS_CWG1B 0b000110
#define PPS_CWG1A 0b000101
#define PPS_CLC4OUT 0b000100
#define PPS_CLC3OUT 0b000011
#define PPS_CLC2OUT 0b000010
#define PPS_CLC1OUT 0b000001
#define PPS_LATxy 0b000000

#endif

/* ************************************************************************** */
// Q43 output values

#if FAMILY_Q43

// Q43 output values
#define PPS_ADGRDB 0x45
#define PPS_ADGRDA 0x44
#define PPS_DSM1 0x43
#define PPS_CLKR 0x42
#define PPS_NCO3 0x41
#define PPS_NCO2 0x40
#define PPS_NCO1 0x3F
#define PPS_TMR0 0x39
#define PPS_I2C1_SDA 0x38
#define PPS_I2C1_SCL 0x37
#define PPS_SPI2_SS 0x36
#define PPS_SPI2_SDO 0x35
#define PPS_SPI2_SCK 0x34
#define PPS_SPI1_SS 0x33
#define PPS_SPI1_SDO 0x32
#define PPS_SPI1_SCK 0x31
#define PPS_C2OUT 0x30
#define PPS_C1OUT 0x2F
#define PPS_UART5_RTS 0x2E
#define PPS_UART5_TXDE 0x2D
#define PPS_UART5_TX 0x2C
#define PPS_UART4_RTS 0x2B
#define PPS_UART4_TXDE 0x2A
#define PPS_UART4_TX 0x29
#define PPS_UART3_RTS 0x28
#define PPS_UART3_TXDE 0x27
#define PPS_UART3_TX 0x26
#define PPS_UART2_RTS 0x25
#define PPS_UART2_TXDE 0x24
#define PPS_UART2_TX 0x23
#define PPS_UART1_RTS 0x22
#define PPS_UART1_TXDE 0x21
#define PPS_UART1_TX 0x20
#define PPS_PWM3S1P2_OUT 0x1D
#define PPS_PWM3S1P1_OUT 0x1C
#define PPS_PWM2S1P2_OUT 0x1B
#define PPS_PWM2S1P1_OUT 0x1A
#define PPS_PWM1S1P2_OUT 0x19
#define PPS_PWM1S1P1_OUT 0x18
#define PPS_CCP3 0x17
#define PPS_CCP2 0x16
#define PPS_CCP1 0x15
#define PPS_CWG3D 0x14
#define PPS_CWG3C 0x13
#define PPS_CWG3B 0x12
#define PPS_CWG3A 0x11
#define PPS_CWG2D 0x10
#define PPS_CWG2C 0x0F
#define PPS_CWG2B 0x0E
#define PPS_CWG2A 0x0D
#define PPS_CWG1D 0x0C
#define PPS_CWG1C 0x0B
#define PPS_CWG1B 0x0A
#define PPS_CWG1A 0x09
#define PPS_CLC8OUT 0x08
#define PPS_CLC7OUT 0x07
#define PPS_CLC6OUT 0x06
#define PPS_CLC5OUT 0x05
#define PPS_CLC4OUT 0x04
#define PPS_CLC3OUT 0x03
#define PPS_CLC2OUT 0x02
#define PPS_CLC1OUT 0x01
#define PPS_LATxy 0x00

#endif

/* ************************************************************************** */
// Q84 output values

#if FAMILY_Q84

#define CANTX 0x46
#define ADGRDB 0x45
#define ADGRDA 0x44
#define DSM1 0x43
#define CLKR 0x42
#define NCO3 0x41
#define NCO2 0x40
#define NCO1 0x3F
#define TU16B 0x3B
#define TU16A 0x3A
#define TMR0 0x39
#define I2C1_SDA 0x38
#define I2C1_SCL 0x37
#define SPI2_SS 0x36
#define SPI2_SDO 0x35
#define SPI2_SCK 0x34
#define SPI1_SS 0x33
#define SPI1_SDO 0x32
#define SPI1_SCK 0x31
#define C2OUT 0x30
#define C1OUT 0x2F
#define UART5_RTS 0x2E
#define UART5_TXDE 0x2D
#define UART5_TX 0x2C
#define UART4_RTS 0x2B
#define UART4_TXDE 0x2A
#define UART4_TX 0x29
#define UART3_RTS 0x28
#define UART3_TXDE 0x27
#define UART3_TX 0x26
#define UART2_RTS 0x25
#define UART2_TXDE 0x24
#define UART2_TX 0x23
#define UART1_RTS 0x22
#define UART1_TXDE 0x21
#define UART1_TX 0x20
#define PWM4S1P2_OUT 0x1F
#define PWM4S1P1_OUT 0x1E
#define PWM3S1P2_OUT 0x1D
#define PWM3S1P1_OUT 0x1C
#define PWM2S1P2_OUT 0x1B
#define PWM2S1P1_OUT 0x1A
#define PWM1S1P2_OUT 0x19
#define PWM1S1P1_OUT 0x18
#define CCP3 0x17
#define CCP2 0x16
#define CCP1 0x15
#define CWG3D 0x14
#define CWG3C 0x13
#define CWG3B 0x12
#define CWG3A 0x11
#define CWG2D 0x10
#define CWG2C 0x0F
#define CWG2B 0x0E
#define CWG2A 0x0D
#define CWG1D 0x0C
#define CWG1C 0x0B
#define CWG1B 0x0A
#define CWG1A 0x09
#define CLC8OUT 0x08
#define CLC7OUT 0x07
#define CLC6OUT 0x06
#define CLC5OUT 0x05
#define CLC4OUT 0x04
#define CLC3OUT 0x03
#define CLC2OUT 0x02
#define CLC1OUT 0x01
#define LATxy 0x00

#endif

#endif