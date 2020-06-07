#include "pps.h"
#include "pic_header.h"

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
void pps_in_CCP4(pps_input_t pin) { CCP4PPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_SMT1_WINDOW(pps_input_t pin) { SMT1WINPPS = pin; }
void pps_in_SMT1_SIGNAL(pps_input_t pin) { SMT1SIGPPS = pin; }

/* -------------------------------------------------------------------------- */

// void pps_in_CWG1(pps_input_t pin) { CWG1PPS = pin; }
// void pps_in_CWG2(pps_input_t pin) { CWG2PPS = pin; }
// void pps_in_CWG3(pps_input_t pin) { CWG3PPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_DSM_CARRIER_LOW(pps_input_t pin) { MD1CARLPPS = pin; }
void pps_in_DSM_CARRIER_HIGH(pps_input_t pin) { MD1CARHPPS = pin; }
void pps_in_DSM_SOURCE(pps_input_t pin) { MD1SRCPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_CLC1_INPUT(pps_input_t pin) { CLCIN0PPS = pin; }
void pps_in_CLC2_INPUT(pps_input_t pin) { CLCIN1PPS = pin; }
void pps_in_CLC3_INPUT(pps_input_t pin) { CLCIN2PPS = pin; }
void pps_in_CLC4_INPUT(pps_input_t pin) { CLCIN3PPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_ADC_TRIGGER(pps_input_t pin) { ADACTPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_SPI1_CLOCK(pps_input_t pin) { SPI1SCKPPS = pin; }
void pps_in_SPI1_DATA_IN(pps_input_t pin) { SPI1SDIPPS = pin; }
void pps_in_SPI1_SS(pps_input_t pin) { SPI1SSPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_I2C1_CLOCK(pps_input_t pin) { I2C1SCLPPS = pin; }
void pps_in_I2C1_DATA(pps_input_t pin) { I2C1SDAPPS = pin; }
void pps_in_I2C2_CLOCK(pps_input_t pin) { I2C2SCLPPS = pin; }
void pps_in_I2C2_DATA(pps_input_t pin) { I2C2SDAPPS = pin; }

/* -------------------------------------------------------------------------- */

void pps_in_UART1_RX(pps_input_t pin) { U1RXPPS = pin; }
void pps_in_UART1_CTS(pps_input_t pin) { U1CTSPPS = pin; }
void pps_in_UART2_RX(pps_input_t pin) { U2RXPPS = pin; }
void pps_in_UART2_CTS(pps_input_t pin) { U2CTSPPS = pin; }

/* ************************************************************************** */

// ADC Guard Ring Outputs
#define PPS_ADGRDB 0b110010 // | A - C | A - C - - | A - - - - F |
#define PPS_ADGRDA 0b110001 // | A - C | A - C - - | A - - - - F |

void pps_out_ADC_GUARD_RING_B(pps_output_t *pin) { *pin = PPS_ADGRDB; }
void pps_out_ADC_GUARD_RING_A(pps_output_t *pin) { *pin = PPS_ADGRDA; }

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3
#define PPS_CWG3D 0b110000 // | A - C | A - - D - | A - - D - - |
#define PPS_CWG3C 0b101111 // | A - C | A - - D - | A - - D - - |
#define PPS_CWG3B 0b101110 // | A - C | A - - - E | A - - - E - |
#define PPS_CWG3A 0b101101 // | - B C | - B C - - | - B C - - - |

void pps_out_CWG3D(pps_output_t *pin) { *pin = PPS_CWG3D; }
void pps_out_CWG3C(pps_output_t *pin) { *pin = PPS_CWG3C; }
void pps_out_CWG3B(pps_output_t *pin) { *pin = PPS_CWG3B; }
void pps_out_CWG3A(pps_output_t *pin) { *pin = PPS_CWG3A; }

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3
#define PPS_CWG2D 0b101100 // | - B C | - B - D - | - B - D - - |
#define PPS_CWG2C 0b101011 // | - B C | - B - D - | - B - D - - |
#define PPS_CWG2B 0b101010 // | - B C | - B - D - | - B - D - - |
#define PPS_CWG2A 0b101001 // | - B C | - B C - - | - B C - - - |

void pps_out_CWG2D(pps_output_t *pin) { *pin = PPS_CWG2D; }
void pps_out_CWG2C(pps_output_t *pin) { *pin = PPS_CWG2C; }
void pps_out_CWG2B(pps_output_t *pin) { *pin = PPS_CWG2B; }
void pps_out_CWG2A(pps_output_t *pin) { *pin = PPS_CWG2A; }

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3
#define PPS_CWG1D 0b001000 // | - B C | - B - D - | - B - D - - |
#define PPS_CWG1C 0b000111 // | - B C | - B - D - | - B - D - - |
#define PPS_CWG1B 0b000110 // | - B C | - B - D - | - B - D - - |
#define PPS_CWG1A 0b000101 // | - B C | - B C - - | - B C - - - |

void pps_out_CWG1D(pps_output_t *pin) { *pin = PPS_CWG1D; }
void pps_out_CWG1C(pps_output_t *pin) { *pin = PPS_CWG1C; }
void pps_out_CWG1B(pps_output_t *pin) { *pin = PPS_CWG1B; }
void pps_out_CWG1A(pps_output_t *pin) { *pin = PPS_CWG1A; }

/* -------------------------------------------------------------------------- */
// Digital Signal Modulater
#define PPS_DSM1 0b101000 // | A - C | A - - D - | A - - D - - |

void pps_out_DSM1(pps_output_t *pin) { *pin = PPS_DSM1; }

/* -------------------------------------------------------------------------- */
// Reference Clock Output
#define PPS_CLKR 0b100111 // | - B C | - B C - - | - B - - E - |

void pps_out_CLKR(pps_output_t *pin) { *pin = PPS_CLKR; }

/* -------------------------------------------------------------------------- */
// Numerically Controller Oscillator
#define PPS_NCO1 0b100110 // | A - C | A - - D - | A - - D - - |

void pps_out_NCO1(pps_output_t *pin) { *pin = PPS_NCO1; }

/* -------------------------------------------------------------------------- */
// Timer 0 Output
#define PPS_TMR0 0b100101 // | - B C | - B C - - | - - C - - F |

void pps_out_TIMER0(pps_output_t *pin) { *pin = PPS_TMR0; }

/* -------------------------------------------------------------------------- */
// I2C
#define PPS_I2C2_SDA 0b100100 // | - B C | - B - D - | - B - D - - |
#define PPS_I2C2_SCL 0b100011 // | - B C | - B - D - | - B - D - - |
#define PPS_I2C1_SDA 0b100010 // | - B C | - B C - - | - B C - - - |
#define PPS_I2C1_SCL 0b100001 // | - B C | - B C - - | - B C - - - |

void pps_out_I2C2_DATA(pps_output_t *pin) { *pin = PPS_I2C2_SDA; }
void pps_out_I2C2_CLOCK(pps_output_t *pin) { *pin = PPS_I2C2_SCL; }
void pps_out_I2C1_DATA(pps_output_t *pin) { *pin = PPS_I2C1_SDA; }
void pps_out_I2C1_CLOCK(pps_output_t *pin) { *pin = PPS_I2C1_SCL; }

/* -------------------------------------------------------------------------- */
// SPI
#define PPS_SPI1_SS 0b100000  // | A - C | A - - D - | A - - D - - |
#define PPS_SPI1_SDO 0b011111 // | - B C | - B C - - | - B C - - - |
#define PPS_SPI1_SCK 0b011110 // | - B C | - B C - - | - B C - - - |

void pps_out_SPI1_SS(pps_output_t *pin) { *pin = PPS_SPI1_SS; }
void pps_out_SPI1_DATA_OUT(pps_output_t *pin) { *pin = PPS_SPI1_SDO; }
void pps_out_SPI1_CLOCK(pps_output_t *pin) { *pin = PPS_SPI1_SCK; }

/* -------------------------------------------------------------------------- */
// Comparator
#define PPS_C2OUT 0b011101 // | A - C | A - - - E | A - - - E - |
#define PPS_C1OUT 0b011100 // | A - C | A - - D - | A - - D - - |

void pps_out_COMPARATOR_2(pps_output_t *pin) { *pin = PPS_C2OUT; }
void pps_out_COMPARATOR_1(pps_output_t *pin) { *pin = PPS_C1OUT; }

/* -------------------------------------------------------------------------- */
// UART 2
#define PPS_UART2_RTS 0b011000  // | - B C | - B - D - | - B - D - - |
#define PPS_UART2_TXDE 0b010111 // | - B C | - B - D - | - B - D - - |
#define PPS_UART2_TX 0b010110   // | - B C | - B - D - | - B - D - - |

void pps_out_UART2_RTS(pps_output_t *pin) { *pin = PPS_UART2_RTS; }
void pps_out_UART2_TXDE(pps_output_t *pin) { *pin = PPS_UART2_TXDE; }
void pps_out_UART2_TX(pps_output_t *pin) { *pin = PPS_UART2_TX; }

/* -------------------------------------------------------------------------- */
// UART 1
#define PPS_UART1_RTS 0b010101  // | - B C | - B C - - | - - C - - F |
#define PPS_UART1_TXDE 0b010100 // | - B C | - B C - - | - - C - - F |
#define PPS_UART1_TX 0b010011   // | - B C | - B C - - | - - C - - F |

void pps_out_UART1_RTS(pps_output_t *pin) { *pin = PPS_UART1_RTS; }
void pps_out_UART1_TXDE(pps_output_t *pin) { *pin = PPS_UART1_TXDE; }
void pps_out_UART1_TX(pps_output_t *pin) { *pin = PPS_UART1_TX; }
/* -------------------------------------------------------------------------- */
// PWM
#define PPS_PWM8 0b010000 // | A - C | A - - D - | A - - D - - |
#define PPS_PWM7 0b001111 // | A - C | A - C - - | - - C - - F |
#define PPS_PWM6 0b001110 // | A - C | A - - D - | A - - D - - |
#define PPS_PWM5 0b001101 // | A - C | A - C - - | A - - D - F |

void pps_out_PWM8(pps_output_t *pin) { *pin = PPS_PWM8; }
void pps_out_PWM7(pps_output_t *pin) { *pin = PPS_PWM7; }
void pps_out_PWM6(pps_output_t *pin) { *pin = PPS_PWM6; }
void pps_out_PWM5(pps_output_t *pin) { *pin = PPS_PWM5; }

/* -------------------------------------------------------------------------- */
// Capture/Compare
#define PPS_CCP4 0b001100 // | - B C | - B - D - | - B - D - - |
#define PPS_CCP3 0b001011 // | - B C | - B - D - | - B - D - - |
#define PPS_CCP2 0b001010 // | - B C | - B C - - | - - C - - F |
#define PPS_CCP1 0b001001 // | - B C | - B C - - | - - C - - F |

void pps_out_CCP4(pps_output_t *pin) { *pin = PPS_CCP4; }
void pps_out_CCP3(pps_output_t *pin) { *pin = PPS_CCP3; }
void pps_out_CCP2(pps_output_t *pin) { *pin = PPS_CCP2; }
void pps_out_CCP1(pps_output_t *pin) { *pin = PPS_CCP1; }

/* -------------------------------------------------------------------------- */
// Configurable Logic Cell
#define PPS_CLC4OUT 0b000100 // | - B C | - B - D - | - B - D - - |
#define PPS_CLC3OUT 0b000011 // | - B C | - B - D - | - B - D - - |
#define PPS_CLC2OUT 0b000010 // | A - C | A - C - - | A - - - - F |
#define PPS_CLC1OUT 0b000001 // | A - C | A - C - - | A - - - - F |

void pps_out_CLC4_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC4OUT; }
void pps_out_CLC3_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC3OUT; }
void pps_out_CLC2_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC2OUT; }
void pps_out_CLC1_OUTPUT(pps_output_t *pin) { *pin = PPS_CLC1OUT; }

/* -------------------------------------------------------------------------- */
// Default value of all RXYPPS registers at RESET
// Primarily used to revert a PPS configuration
#define PPS_LATxy 0b000000 // | A B C | A B C D E | A B C D E F |

void pps_out_LATCH(pps_output_t *pin) { *pin = PPS_LATxy; }