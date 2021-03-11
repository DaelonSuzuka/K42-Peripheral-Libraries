#include "pps.h"
#include "pic_header.h"
#include "pps_values.h"

/* ************************************************************************** */

void pps_unlock(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;
}

void pps_lock(void) {
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01;
}

/* ************************************************************************** */

void pps_in_INTERRUPT0(pps_input_t pin) { INT0PPS = pin; }
void pps_in_INTERRUPT1(pps_input_t pin) { INT1PPS = pin; }
void pps_in_INTERRUPT2(pps_input_t pin) { INT2PPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_TIMER0_CLOCK(pps_input_t pin) { T0CKIPPS = pin; }
void pps_in_TIMER1_CLOCK(pps_input_t pin) { T1CKIPPS = pin; }
void pps_in_TIMER1_GATE(pps_input_t pin) { T1GPPS = pin; }
void pps_in_TIMER3_CLOCK(pps_input_t pin) { T3CKIPPS = pin; }
void pps_in_TIMER3_GATE(pps_input_t pin) { T3GPPS = pin; }
void pps_in_TIMER5_CLOCK(pps_input_t pin) { T5CKIPPS = pin; }
void pps_in_TIMER5_GATE(pps_input_t pin) { T5GPPS = pin; }
void pps_in_TIMER2_CLOCK(pps_input_t pin) { T2INPPS = pin; }
void pps_in_TIMER4_CLOCK(pps_input_t pin) { T4INPPS = pin; }
void pps_in_TIMER6_CLOCK(pps_input_t pin) { T6INPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_CCP1(pps_input_t pin) { CCP1PPS = pin; }
void pps_in_CCP2(pps_input_t pin) { CCP2PPS = pin; }
void pps_in_CCP3(pps_input_t pin) { CCP3PPS = pin; }
#ifdef CCP4PPS
void pps_in_CCP4(pps_input_t pin) { CCP4PPS = pin; }
#endif

/* -------------------------------------------------------------------------- */

#ifdef PWMIN0PPS
void pps_in_PWM_Input_0(pps_input_t pin) { PWMIN0PPS = pin; }
void pps_in_PWM_Input_1(pps_input_t pin) { PWMIN1PPS = pin; }
void pps_in_PWM1_External_Reset(pps_input_t pin) { PWM1ERSPPS = pin; }
void pps_in_PWM2_External_Reset(pps_input_t pin) { PWM2ERSPPS = pin; }
void pps_in_PWM3_External_Reset(pps_input_t pin) { PWM3ERSPPS = pin; }
#endif

/* -------------------------------------------------------------------------- */

void pps_in_SMT1_WINDOW(pps_input_t pin) { SMT1WINPPS = pin; }
void pps_in_SMT1_SIGNAL(pps_input_t pin) { SMT1SIGPPS = pin; }

/* -------------------------------------------------------------------------- */

#ifdef CWG1PPS
void pps_in_CWG1(pps_input_t pin) { CWG1PPS = pin; }
void pps_in_CWG2(pps_input_t pin) { CWG2PPS = pin; }
void pps_in_CWG3(pps_input_t pin) { CWG3PPS = pin; }
#endif

/* -------------------------------------------------------------------------- */

void pps_in_DSM_CARRIER_LOW(pps_input_t pin) { MD1CARLPPS = pin; }
void pps_in_DSM_CARRIER_HIGH(pps_input_t pin) { MD1CARHPPS = pin; }
void pps_in_DSM_SOURCE(pps_input_t pin) { MD1SRCPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_CLC1_INPUT(pps_input_t pin) { CLCIN0PPS = pin; }
void pps_in_CLC2_INPUT(pps_input_t pin) { CLCIN1PPS = pin; }
void pps_in_CLC3_INPUT(pps_input_t pin) { CLCIN2PPS = pin; }
void pps_in_CLC4_INPUT(pps_input_t pin) { CLCIN3PPS = pin; }
#ifdef CLCIN4PPS
void pps_in_CLC5_INPUT(pps_input_t pin) { CLCIN4PPS = pin; }
void pps_in_CLC6_INPUT(pps_input_t pin) { CLCIN5PPS = pin; }
void pps_in_CLC7_INPUT(pps_input_t pin) { CLCIN6PPS = pin; }
void pps_in_CLC8_INPUT(pps_input_t pin) { CLCIN7PPS = pin; }
#endif

/* -------------------------------------------------------------------------- */

void pps_in_ADC_TRIGGER(pps_input_t pin) { ADACTPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_SPI1_CLOCK(pps_input_t pin) { SPI1SCKPPS = pin; }
void pps_in_SPI1_DATA_IN(pps_input_t pin) { SPI1SDIPPS = pin; }
void pps_in_SPI1_SS(pps_input_t pin) { SPI1SSPPS = pin; }
#ifdef SPI2SCKPPS
void pps_in_SPI2_CLOCK(pps_input_t pin) { SPI2SCKPPS = pin; }
void pps_in_SPI2_DATA_IN(pps_input_t pin) { SPI2SDIPPS = pin; }
void pps_in_SPI2_SS(pps_input_t pin) { SPI2SSPPS = pin; }
#endif

/* -------------------------------------------------------------------------- */

void pps_in_I2C1_CLOCK(pps_input_t pin) { I2C1SCLPPS = pin; }
void pps_in_I2C1_DATA(pps_input_t pin) { I2C1SDAPPS = pin; }
#ifdef I2C2SCLPPS
void pps_in_I2C2_CLOCK(pps_input_t pin) { I2C2SCLPPS = pin; }
void pps_in_I2C2_DATA(pps_input_t pin) { I2C2SDAPPS = pin; }
#endif

/* -------------------------------------------------------------------------- */

void pps_in_UART1_RX(pps_input_t pin) { U1RXPPS = pin; }
void pps_in_UART1_CTS(pps_input_t pin) { U1CTSPPS = pin; }
void pps_in_UART2_RX(pps_input_t pin) { U2RXPPS = pin; }
void pps_in_UART2_CTS(pps_input_t pin) { U2CTSPPS = pin; }
#ifdef U3RXPPS
void pps_in_UART3_RX(pps_input_t pin) { U3RXPPS = pin; }
void pps_in_UART3_CTS(pps_input_t pin) { U3CTSPPS = pin; }
#endif
#ifdef U4RXPPS
void pps_in_UART4_RX(pps_input_t pin) { U4RXPPS = pin; }
void pps_in_UART4_CTS(pps_input_t pin) { U4CTSPPS = pin; }
void pps_in_UART5_RX(pps_input_t pin) { U5RXPPS = pin; }
void pps_in_UART5_CTS(pps_input_t pin) { U5CTSPPS = pin; }
#endif

/* ************************************************************************** */

// ADC Guard Ring Outputs

void pps_out_ADC_GUARD_RING_B(pps_output_t *pin) { *pin = PPS_ADGRDB; }
void pps_out_ADC_GUARD_RING_A(pps_output_t *pin) { *pin = PPS_ADGRDA; }

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3

void pps_out_CWG3D(pps_output_t *pin) { *pin = PPS_CWG3D; }
void pps_out_CWG3C(pps_output_t *pin) { *pin = PPS_CWG3C; }
void pps_out_CWG3B(pps_output_t *pin) { *pin = PPS_CWG3B; }
void pps_out_CWG3A(pps_output_t *pin) { *pin = PPS_CWG3A; }

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 2

void pps_out_CWG2D(pps_output_t *pin) { *pin = PPS_CWG2D; }
void pps_out_CWG2C(pps_output_t *pin) { *pin = PPS_CWG2C; }
void pps_out_CWG2B(pps_output_t *pin) { *pin = PPS_CWG2B; }
void pps_out_CWG2A(pps_output_t *pin) { *pin = PPS_CWG2A; }

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 1

void pps_out_CWG1D(pps_output_t *pin) { *pin = PPS_CWG1D; }
void pps_out_CWG1C(pps_output_t *pin) { *pin = PPS_CWG1C; }
void pps_out_CWG1B(pps_output_t *pin) { *pin = PPS_CWG1B; }
void pps_out_CWG1A(pps_output_t *pin) { *pin = PPS_CWG1A; }

/* -------------------------------------------------------------------------- */
// Data Signal Modulater

void pps_out_DSM1(pps_output_t *pin) { *pin = PPS_DSM1; }

/* -------------------------------------------------------------------------- */
// Reference Clock Output

void pps_out_CLKR(pps_output_t *pin) { *pin = PPS_CLKR; }

/* -------------------------------------------------------------------------- */
// Numerically Controller Oscillator

#ifdef PPS_NCO3
void pps_out_NCO3(pps_output_t *pin) { *pin = PPS_NCO3; }
void pps_out_NCO2(pps_output_t *pin) { *pin = PPS_NCO2; }
#endif
void pps_out_NCO1(pps_output_t *pin) { *pin = PPS_NCO1; }

/* -------------------------------------------------------------------------- */
// Timer 0 Output

void pps_out_TIMER0(pps_output_t *pin) { *pin = PPS_TMR0; }

/* -------------------------------------------------------------------------- */
// I2C

void pps_out_I2C1_DATA(pps_output_t *pin) { *pin = PPS_I2C1_SDA; }
void pps_out_I2C1_CLOCK(pps_output_t *pin) { *pin = PPS_I2C1_SCL; }
#ifdef PPS_I2C2_SCL
void pps_out_I2C2_DATA(pps_output_t *pin) { *pin = PPS_I2C2_SDA; }
void pps_out_I2C2_CLOCK(pps_output_t *pin) { *pin = PPS_I2C2_SCL; }
#endif

/* -------------------------------------------------------------------------- */
// SPI

void pps_out_SPI1_SS(pps_output_t *pin) { *pin = PPS_SPI1_SS; }
void pps_out_SPI1_DATA_OUT(pps_output_t *pin) { *pin = PPS_SPI1_SDO; }
void pps_out_SPI1_CLOCK(pps_output_t *pin) { *pin = PPS_SPI1_SCK; }
#ifdef PPS_SPI2_SCK
void pps_out_SPI2_SS(pps_output_t *pin) { *pin = PPS_SPI2_SS; }
void pps_out_SPI2_DATA_OUT(pps_output_t *pin) { *pin = PPS_SPI2_SDO; }
void pps_out_SPI2_CLOCK(pps_output_t *pin) { *pin = PPS_SPI2_SCK; }
#endif

/* -------------------------------------------------------------------------- */
// Comparator

void pps_out_COMPARATOR_2(pps_output_t *pin) { *pin = PPS_C2OUT; }
void pps_out_COMPARATOR_1(pps_output_t *pin) { *pin = PPS_C1OUT; }

/* -------------------------------------------------------------------------- */
// UART 5

#ifdef PPS_UART5_TX
void pps_out_UART5_RTS(pps_output_t *pin) { *pin = PPS_UART5_RTS; }
void pps_out_UART5_TXDE(pps_output_t *pin) { *pin = PPS_UART5_TXDE; }
void pps_out_UART5_TX(pps_output_t *pin) { *pin = PPS_UART5_TX; }
#endif

/* -------------------------------------------------------------------------- */
// UART 4

#ifdef PPS_UART4_TX
void pps_out_UART4_RTS(pps_output_t *pin) { *pin = PPS_UART4_RTS; }
void pps_out_UART4_TXDE(pps_output_t *pin) { *pin = PPS_UART4_TXDE; }
void pps_out_UART4_TX(pps_output_t *pin) { *pin = PPS_UART4_TX; }
#endif

/* -------------------------------------------------------------------------- */
// UART 3

#ifdef PPS_UART3_TX
void pps_out_UART3_RTS(pps_output_t *pin) { *pin = PPS_UART3_RTS; }
void pps_out_UART3_TXDE(pps_output_t *pin) { *pin = PPS_UART3_TXDE; }
void pps_out_UART3_TX(pps_output_t *pin) { *pin = PPS_UART3_TX; }
#endif

/* -------------------------------------------------------------------------- */
// UART 2

void pps_out_UART2_RTS(pps_output_t *pin) { *pin = PPS_UART2_RTS; }
void pps_out_UART2_TXDE(pps_output_t *pin) { *pin = PPS_UART2_TXDE; }
void pps_out_UART2_TX(pps_output_t *pin) { *pin = PPS_UART2_TX; }

/* -------------------------------------------------------------------------- */
// UART 1

void pps_out_UART1_RTS(pps_output_t *pin) { *pin = PPS_UART1_RTS; }
void pps_out_UART1_TXDE(pps_output_t *pin) { *pin = PPS_UART1_TXDE; }
void pps_out_UART1_TX(pps_output_t *pin) { *pin = PPS_UART1_TX; }
/* -------------------------------------------------------------------------- */
// PWM

#ifdef PPS_PWM5
void pps_out_PWM8(pps_output_t *pin) { *pin = PPS_PWM8; }
void pps_out_PWM7(pps_output_t *pin) { *pin = PPS_PWM7; }
void pps_out_PWM6(pps_output_t *pin) { *pin = PPS_PWM6; }
void pps_out_PWM5(pps_output_t *pin) { *pin = PPS_PWM5; }
#endif

#ifdef PPS_PWM1S1P1_OUT
void pps_out_PWM3S1P2(pps_output_t *pin) { *pin = PPS_PWM3S1P2_OUT; }
void pps_out_PWM3S1P1(pps_output_t *pin) { *pin = PPS_PWM3S1P1_OUT; }
void pps_out_PWM2S1P2(pps_output_t *pin) { *pin = PPS_PWM2S1P2_OUT; }
void pps_out_PWM2S1P1(pps_output_t *pin) { *pin = PPS_PWM2S1P1_OUT; }
void pps_out_PWM1S1P2(pps_output_t *pin) { *pin = PPS_PWM1S1P2_OUT; }
void pps_out_PWM1S1P1(pps_output_t *pin) { *pin = PPS_PWM1S1P1_OUT; }
#endif

/* -------------------------------------------------------------------------- */
// Capture/Compare

#ifdef PPS_CCP4
void pps_out_CCP4(pps_output_t *pin) { *pin = PPS_CCP4; }
#endif
void pps_out_CCP3(pps_output_t *pin) { *pin = PPS_CCP3; }
void pps_out_CCP2(pps_output_t *pin) { *pin = PPS_CCP2; }
void pps_out_CCP1(pps_output_t *pin) { *pin = PPS_CCP1; }

/* -------------------------------------------------------------------------- */
// Configurable Logic Cell

#ifdef PPS_CLC8OUT
void pps_out_CLC8_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC8OUT; }
void pps_out_CLC7_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC7OUT; }
void pps_out_CLC6_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC6OUT; }
void pps_out_CLC5_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC5OUT; }
#endif
void pps_out_CLC4_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC4OUT; }
void pps_out_CLC3_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC3OUT; }
void pps_out_CLC2_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC2OUT; }
void pps_out_CLC1_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC1OUT; }

/* -------------------------------------------------------------------------- */
// Default value of all RXYPPS registers at RESET
// Primarily used to revert a PPS configuration

void pps_out_LATCH(pps_output_t *pin) { *pin = PPS_LATxy; }