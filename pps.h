#ifndef _PPS_H_
#define _PPS_H_

/* ************************************************************************** */

/*  Notes on using the PPS (Peripheral Pin Select)

    The PIC18 K42 family microcontrollers has a Peripheral Pin Select module
    that allows the remapping of digital I/O pins.
*/

/* ************************************************************************** */

/*  Notes on managing the PPS Lock

    These macros are designed to help each software module manage its own PPS
    settings. Writes to PPS registers while the system is locked are ignored.

    Each software module is responsible for putting its required PPS setup code
    in it's module_init(). If all the various module_init() calls are collected
    into one place, like startup(), then the block of _init() calls can be
    wrapped with these two macros, and the entire system's PPS requirements can
    be satisfied in one shot.
*/

extern void pps_unlock(void);
extern void pps_lock(void);

/* ************************************************************************** */
/*  PPS Input Registers

    Example PPS Input assignments:

    Connecting the Timer 3 Clock input to pin RB0:
    pps_in_TIMER3_CLOCK(PPS_IN(B, 0));

    Connecting the UART 1 Recieve input to pin RC7:
    pps_in_UART1_RX(PPS_IN(C, 7));

    Connecting the ADC Trigger input to RA4, through a function call:
    void some_init(pps_input_t pin){
        pps_in_ADC_TRIGGER(pin);
    }

    void some_other_function(void) {
        some_init(PPS_IN(A, 4));
    }
*/

// Can be used to pass PPS pins into a function
typedef unsigned char pps_input_t;

// macro to help abbreviate
#define PPS_INPUT(port, pin) (PPS_PORT_##port & PPS_PIN_##pin)

/* -------------------------------------------------------------------------- */

// Input pin assignment macros
#define PPS_PORT_A 0b11000111
#define PPS_PORT_B 0b11001111
#define PPS_PORT_C 0b11010111
#define PPS_PORT_D 0b11011111
#define PPS_PORT_E 0b11100111
#define PPS_PORT_F 0b11101111

#define PPS_PIN_0 0b11111000
#define PPS_PIN_1 0b11111001
#define PPS_PIN_2 0b11111010
#define PPS_PIN_3 0b11111011
#define PPS_PIN_4 0b11111100
#define PPS_PIN_5 0b11111101
#define PPS_PIN_6 0b11111110
#define PPS_PIN_7 0b11111111

/* -------------------------------------------------------------------------- */

// Interrupt 0  (RB0) | A B - | A B - - - | A B - - - - |
// Interrupt 1  (RB1) | A B - | A B - - - | - B - D - - |
// Interrupt 2  (RB2) | A B - | A B - - - | - B - - - F |

extern void pps_in_INTERRUPT0(pps_input_t pin);
extern void pps_in_INTERRUPT1(pps_input_t pin);
extern void pps_in_INTERRUPT2(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// Timer0 Clock (RA4) | A B - | A B - - - | A - - - - F |
// Timer1 Clock (RC0) | A - C | A - C - - | - - C - E - |
// Timer1 Gate  (RB5) | - B C | - B C - - | - B C - - - |
// Timer3 Clock (RC0) | - B C | - B C - - | - - C - E - |
// Timer3 Gate  (RC0) | A - C | A - C - - | A - C - - - |
// Timer5 Clock (RC2) | A - C | A - C - - | - - C - E - |
// Timer5 Gate  (RB4) | - B C | - B - D - | - B - D - - |
// Timer2 Clock (RC3) | A - C | A - C - - | A - C - - - |
// Timer4 Clock (RC5) | - B C | - B C - - | - B C - - - |
// Timer6 Clock (RB7) | - B C | - B - D - | - B - D - - |

extern void pps_in_TIMER0_CLOCK(pps_input_t pin);
extern void pps_in_TIMER1_CLOCK(pps_input_t pin);
extern void pps_in_TIMER1_GATE(pps_input_t pin);
extern void pps_in_TIMER3_CLOCK(pps_input_t pin);
extern void pps_in_TIMER3_GATE(pps_input_t pin);
extern void pps_in_TIMER5_CLOCK(pps_input_t pin);
extern void pps_in_TIMER5_GATE(pps_input_t pin);
extern void pps_in_TIMER2_CLOCK(pps_input_t pin);
extern void pps_in_TIMER4_CLOCK(pps_input_t pin);
extern void pps_in_TIMER6_CLOCK(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// CCP1 (RC2) | - B C | - B C - - | - - C - - F |
// CCP2 (RC1) | - B C | - B C - - | - - C - - F |
// CCP3 (RB5) | - B C | - B - D - | - B - D - - |
// CCP4 (RB0) | - B C | - B - D - | - B - D - - |

extern void pps_in_CCP1(pps_input_t pin);
extern void pps_in_CCP2(pps_input_t pin);
extern void pps_in_CCP3(pps_input_t pin);
extern void pps_in_CCP4(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// SMT1 Window (RC0) | - B C | - B C - - | - - C - - F |
// SMT1 Signal (RC1) | - B C | - B C - - | - - C - - F |

extern void pps_in_SMT1_WINDOW(pps_input_t pin);
extern void pps_in_SMT1_SIGNAL(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// CWG1 (RB0) | - B C | - B - D - | - B - D - - |
// CWG2 (RB1) | - B C | - B - D - | - B - D - - |
// CWG3 (RB2) | - B C | - B - D - | - B - D - - |

// extern void pps_in_CWG1(pps_input_t pin);
// extern void pps_in_CWG2(pps_input_t pin);
// extern void pps_in_CWG3(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// DSM1 Carrier Low     (RA3) | A - C | A - - D - | A - - D - - |
// DSM1 Carrier High    (RA4) | A - C | A - - D - | A - - D - - |
// DSM1 Source          (RA5) | A - C | A - - D - | A - - D - - |

extern void pps_in_DSM_CARRIER_LOW(pps_input_t pin);
extern void pps_in_DSM_CARRIER_HIGH(pps_input_t pin);
extern void pps_in_DSM_SOURCE(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// CLCx Input 1 (RA0) | A - C | A - C - - | A - C - - - |
// CLCx Input 2 (RA1) | A - C | A - C - - | A - C - - - |
// CLCx Input 3 (RB6) | - B C | - B - D - | - B - D - - |
// CLCx Input 4 (RB7) | - B C | - B - D - | - B - D - - |

extern void pps_in_CLC1_INPUT(pps_input_t pin);
extern void pps_in_CLC2_INPUT(pps_input_t pin);
extern void pps_in_CLC3_INPUT(pps_input_t pin);
extern void pps_in_CLC4_INPUT(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// ADC Conversion Trigger (RB4) | - B C | - B - D - | - B - D - - |

extern void pps_in_ADC_TRIGGER(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// SPI1 Clock           (RC3) | - B C | - B C - - | - B C - - - |
// SPI1 Data            (RC4) | - B C | - B C - - | - B C - - - |
// SPI1 Slave Select    (RA5) | A - C | A - - D - | A - - D - - |

extern void pps_in_SPI1_CLOCK(pps_input_t pin);
extern void pps_in_SPI1_DATA_IN(pps_input_t pin);
extern void pps_in_SPI1_SS(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// I2C1 Clock   (RC3) | - B C | - B C - - | - B C - - - |
// I2C1 Data    (RC4) | - B C | - B C - - | - B C - - - |
// I2C2 Clock   (RB1) | - B C | - B - D - | - B - D - - |
// I2C2 Data    (RB2) | - B C | - B - D - | - B - D - - |

extern void pps_in_I2C1_CLOCK(pps_input_t pin);
extern void pps_in_I2C1_DATA(pps_input_t pin);
extern void pps_in_I2C2_CLOCK(pps_input_t pin);
extern void pps_in_I2C2_DATA(pps_input_t pin);

/* -------------------------------------------------------------------------- */

// UART1 Receive        (RC7) | - B C | - B C - - | - - C - - F |
// UART1 Clear To Send  (RC6) | - B C | - B C - - | - - C - - F |
// UART2 Receive        (RB7) | - B C | - B - D - | - B - D - - |
// UART2 Clear To Send  (RB6) | - B C | - B - D - | - B - D - - |

extern void pps_in_UART1_RX(pps_input_t pin);
extern void pps_in_UART1_CTS(pps_input_t pin);
extern void pps_in_UART2_RX(pps_input_t pin);
extern void pps_in_UART2_CTS(pps_input_t pin);

/* ************************************************************************** */
/*  PPS Output Registers

    Example PPS Output assignments:

    Assigning UART1 TX to pin RC6:
    pps_out_UART1_TX(RC6PPS)

    Assigning the output of PWM5 to RB2, through a function call:
    void some_init(pps_output_t* outputPin){
        pps_out_PWM5(outputPin);
    }

    void some_other_function(void) {
        some_init(PPS_OUT(B, 2));
    }
*/

// Can be used to pass PPS pins into a function
typedef volatile unsigned char pps_output_t;

//
#define PPS_OUTPUT(port, pin) (&R##port##pin##PPS)

/* -------------------------------------------------------------------------- */
// ADC Guard Ring Outputs
// ADGRDB | A - C | A - C - - | A - - - - F |
// ADGRDA | A - C | A - C - - | A - - - - F |

extern void pps_out_ADC_GUARD_RING_B(pps_output_t *pin);
extern void pps_out_ADC_GUARD_RING_A(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3
// CWG3D | A - C | A - - D - | A - - D - - |
// CWG3C | A - C | A - - D - | A - - D - - |
// CWG3B | A - C | A - - - E | A - - - E - |
// CWG3A | - B C | - B C - - | - B C - - - |

extern void pps_out_CWG3D(pps_output_t *pin);
extern void pps_out_CWG3C(pps_output_t *pin);
extern void pps_out_CWG3B(pps_output_t *pin);
extern void pps_out_CWG3A(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3
// CWG2D | - B C | - B - D - | - B - D - - |
// CWG2C | - B C | - B - D - | - B - D - - |
// CWG2B | - B C | - B - D - | - B - D - - |
// CWG2A | - B C | - B C - - | - B C - - - |

extern void pps_out_CWG2D(pps_output_t *pin);
extern void pps_out_CWG2C(pps_output_t *pin);
extern void pps_out_CWG2B(pps_output_t *pin);
extern void pps_out_CWG2A(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Complementary Waveform Generator 3
// CWG1D | - B C | - B - D - | - B - D - - |
// CWG1C | - B C | - B - D - | - B - D - - |
// CWG1B | - B C | - B - D - | - B - D - - |
// CWG1A | - B C | - B C - - | - B C - - - |

extern void pps_out_CWG1D(pps_output_t *pin);
extern void pps_out_CWG1C(pps_output_t *pin);
extern void pps_out_CWG1B(pps_output_t *pin);
extern void pps_out_CWG1A(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Digital Signal Modulater
// DSM1 | A - C | A - - D - | A - - D - - |

extern void pps_out_DSM1(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Reference Clock Output
// CLKR | - B C | - B C - - | - B - - E - |

extern void pps_out_CLKR(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Numerically Controller Oscillator
// NCO1 | A - C | A - - D - | A - - D - - |

extern void pps_out_NCO1(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Timer 0 Output
// TMR0 | - B C | - B C - - | - - C - - F |

extern void pps_out_TIMER0(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// I2C
// I2C2_SDA | - B C | - B - D - | - B - D - - |
// I2C2_SCL | - B C | - B - D - | - B - D - - |
// I2C1_SDA | - B C | - B C - - | - B C - - - |
// I2C1_SCL | - B C | - B C - - | - B C - - - |

extern void pps_out_I2C2_DATA(pps_output_t *pin);
extern void pps_out_I2C2_CLOCK(pps_output_t *pin);
extern void pps_out_I2C1_DATA(pps_output_t *pin);
extern void pps_out_I2C1_CLOCK(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// SPI
// SPI1_SS  | A - C | A - - D - | A - - D - - |
// SPI1_SDO | - B C | - B C - - | - B C - - - |
// SPI1_SCK | - B C | - B C - - | - B C - - - |

extern void pps_out_SPI1_SS(pps_output_t *pin);
extern void pps_out_SPI1_DATA_OUT(pps_output_t *pin);
extern void pps_out_SPI1_CLOCK(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Comparator
// C2OUT | A - C | A - - - E | A - - - E - |
// C1OUT | A - C | A - - D - | A - - D - - |

extern void pps_out_COMPARATOR_2(pps_output_t *pin);
extern void pps_out_COMPARATOR_1(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// UART 2
// UART2_RTS  | - B C | - B - D - | - B - D - - |
// UART2_TXDE | - B C | - B - D - | - B - D - - |
// UART2_TX   | - B C | - B - D - | - B - D - - |

extern void pps_out_UART2_RTS(pps_output_t *pin);
extern void pps_out_UART2_TXDE(pps_output_t *pin);
extern void pps_out_UART2_TX(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// UART 1
// UART1_RTS  | - B C | - B C - - | - - C - - F |
// UART1_TXDE | - B C | - B C - - | - - C - - F |
// UART1_TX   | - B C | - B C - - | - - C - - F |

extern void pps_out_UART1_RTS(pps_output_t *pin);
extern void pps_out_UART1_TXDE(pps_output_t *pin);
extern void pps_out_UART1_TX(pps_output_t *pin);
/* -------------------------------------------------------------------------- */
// PWM
// PWM8 | A - C | A - - D - | A - - D - - |
// PWM7 | A - C | A - C - - | - - C - - F |
// PWM6 | A - C | A - - D - | A - - D - - |
// PWM5 | A - C | A - C - - | A - - D - F |

extern void pps_out_PWM8(pps_output_t *pin);
extern void pps_out_PWM7(pps_output_t *pin);
extern void pps_out_PWM6(pps_output_t *pin);
extern void pps_out_PWM5(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Capture/Compare
// CCP4 | - B C | - B - D - | - B - D - - |
// CCP3 | - B C | - B - D - | - B - D - - |
// CCP2 | - B C | - B C - - | - - C - - F |
// CCP1 | - B C | - B C - - | - - C - - F |

extern void pps_out_CCP4(pps_output_t *pin);
extern void pps_out_CCP3(pps_output_t *pin);
extern void pps_out_CCP2(pps_output_t *pin);
extern void pps_out_CCP1(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Configurable Logic Cell
// CLC4OUT | - B C | - B - D - | - B - D - - |
// CLC3OUT | - B C | - B - D - | - B - D - - |
// CLC2OUT | A - C | A - C - - | A - - - - F |
// CLC1OUT | A - C | A - C - - | A - - - - F |

extern void pps_out_CLC4_OUTPUT(pps_output_t *pin);
extern void pps_out_CLC3_OUTPUT(pps_output_t *pin);
extern void pps_out_CLC2_OUTPUT(pps_output_t *pin);
extern void pps_out_CLC1_OUTPUT(pps_output_t *pin);

/* -------------------------------------------------------------------------- */
// Default value of all RXYPPS registers at RESET
// Primarily used to revert a PPS configuration
// PPS_LATxy | A B C | A B C D E | A B C D E F |

extern void pps_out_LATCH(pps_output_t *pin);

/* ************************************************************************** */

#endif /* _PPS_H_ */