#ifndef _PMD_H_
#define _PMD_H_

#include <stdbool.h>

/* ************************************************************************** */

enum pmd_module {
    PMD_SYSC,  // Peripheral System Clock Network 
    PMD_FVR,   // Fixed Voltage Reference
    PMD_HLVD,  // High/Low Voltage Detect
    PMD_CRC,   // CRC
    PMD_SCAN,  // NVM Memory Scanner
    PMD_CLKR,  // Clock Reference
    PMD_IOC,   // Interrupt-on-change
    PMD_SMT1,  // Signal Measurement Timer
    PMD_TMR0,  // Timer 0
    PMD_TMR1,  // Timer 1
    PMD_TMR2,  // Timer 2
    PMD_TMR3,  // Timer 3
    PMD_TMR4,  // Timer 4
    PMD_TMR5,  // Timer 5
    PMD_TMR6,  // Timer 6
    PMD_ACT,   // Active Clock Tuning
    PMD_DAC1,  // Digital-to-Analog Converter
    PMD_ADC,   // Analog-to-Digital Converter
    PMD_CM2,   // Comparator 2
    PMD_CM1,   // Comparator 1
    PMD_ZCD,   // Zero-Crossing Detector
    PMD_CWG3,  // Configurable Waveform Generator 3
    PMD_CWG2,  // Configurable Waveform Generator 2
    PMD_CWG1,  // Configurable Waveform Generator 1
    PMD_DSM1,  // Data Signal Modulator
    PMD_NCO3,  // Numerically Controller Oscillator 3
    PMD_NCO2,  // Numerically Controller Oscillator 2
    PMD_NCO1,  // Numerically Controller Oscillator 1
    PMD_PWM3,  // Pulse Width Modulator 3
    PMD_PWM2,  // Pulse Width Modulator 2
    PMD_PWM1,  // Pulse Width Modulator 1
    PMD_CCP3,  // Capture/Compare 3
    PMD_CCP2,  // Capture/Compare 2
    PMD_CCP1,  // Capture/Compare 1
    PMD_UART5, // UART5
    PMD_UART4, // UART4
    PMD_UART3, // UART3
    PMD_UART2, // UART2
    PMD_UART1, // UART1
    PMD_SPI2,  // Serial Peripheral Interface 2
    PMD_SPI1,  // Serial Peripheral Interface 1
    PMD_I2C1,  // I2C
    PMD_CLC8,  // Configurable Logic Cell 8
    PMD_CLC7,  // Configurable Logic Cell 7
    PMD_CLC6,  // Configurable Logic Cell 6
    PMD_CLC5,  // Configurable Logic Cell 5
    PMD_CLC4,  // Configurable Logic Cell 4
    PMD_CLC3,  // Configurable Logic Cell 3
    PMD_CLC2,  // Configurable Logic Cell 2
    PMD_CLC1,  // Configurable Logic Cell 1
    PMD_DMA6,  // Direct Memory Access 6
    PMD_DMA5,  // Direct Memory Access 5
    PMD_DMA4,  // Direct Memory Access 4
    PMD_DMA3,  // Direct Memory Access 3
    PMD_DMA2,  // Direct Memory Access 2
    PMD_DMA1,  // Direct Memory Access 1
};

/* ************************************************************************** */

// enable or disable the given module
void pmd_set(enum pmd_module module, bool state);

#endif // _PMD_H_