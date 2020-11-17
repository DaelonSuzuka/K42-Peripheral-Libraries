# K42:

# Inputs:

| Peripheral | Register | Default Pin | 28pin | 40pin | 48pin |
| - | - | - | :-: | :-: | :-: | 
| Interrupt 0 | INT0PPS | RB0  | A B — | A B — — — | A B — — — — |
| Interrupt 1 | INT1PPS | RB1  | A B — | A B — — — | — B — D — — |
| Interrupt 2 | INT2PPS | RB2  | A B — | A B — — — | — B — — — F |
| Timer0 Clock | T0CKIPPS | RA4  | A B — | A B — — — | A — — — — F |
| Timer1 Clock | T1CKIPPS | RC0  | A — C | A — C — — | — — C — E — |
| Timer1 Gate | T1GPPS | RB5  | — B C | — B C — — | — B C — — — |
| Timer3 Clock | T3CKIPPS | RC0  | — B C | — B C — — | - — C — E — |
| Timer3 Gate | T3GPPS | RC0  | A — C | A — C — — | A — C — — — |
| Timer5 Clock | T5CKIPPS | RC2  | A — C | A — C — — | — — C — E — |
| Timer5 Gate | T5GPPS | RB4  | — B C | — B — D — | — B — D — — |
| Timer2 Clock | T2INPPS | RC3  | A — C | A — C — — | A — C — — — |
| Timer4 Clock | T4INPPS | RC5  | — B C | — B C — — | — B C — — — |
| Timer6 Clock | T6INPPS | RB7  | — B C | — B — D — | — B — D — — |
| CCP1 | CCP1PPS | RC2  | — B C | — B C — — | — — C — — F |
| CCP2 | CCP2PPS | RC1  | — B C | — B C — — | — — C — — F |
| CCP3 | CCP3PPS | RB5  | — B C | — B — D — | — B — D — — |
| CCP4 | CCP4PPS | RB0  | — B C | — B — D — | — B — D — — |
| SMT1 Window | SMT1WINPPS | RC0  | — B C | — B C — — | — — C — — F |
| SMT1 Signal | SMT1SIGPPS | RC1  | — B C | — B C — — | — — C — — F |
| CWG1 | CWG1PPS | RB0  | — B C | — B — D — | — B — D — — |
| CWG2 | CWG2PPS | RB1  | — B C | — B — D — | — B — D — — |
| CWG3 | CWG3PPS | RB2  | — B C | — B — D — | — B — D — — |
| DSM1 Carrier Low | MD1CARLPPS | RA3  | A — C | A — — D — | A — — D — — |
| DSM1 Carrier High | MD1CARHPPS | RA4  | A — C | A — — D — | A — — D — — |
| DSM1 Source | MD1SRCPPS | RA5  | A — C | A — — D — | A — — D — — |
| CLCx Input 1 | CLCIN0PPS | RA0  | A — C | A — C — — | A — C — — — |
| CLCx Input 2 | CLCIN1PPS | RA1  | A — C | A — C — — | A — C — — — |
| CLCx Input 3 | CLCIN2PPS | RB6  | — B C | — B — D — | — B — D — — |
| CLCx Input 4 | CLCIN3PPS | RB7  | — B C | — B — D — | — B — D — — |
| ADC Conversion Trigger | ADACTPPS | RB4  | — B C | — B — D — | — B — D — — |
| SPI1 Clock | SPI1SCKPPS | RC3  | — B C | — B C — — | — B C — — — |
| SPI1 Data | SPI1SDIPPS | RC4  | — B C | — B C — — | — B C — — — |
| SPI1 Slave Select | SPI1SSPPS | RA5  | A — C | A — — D — | A — — D — — |
| I 2 C1 Clock | I2C1SCLPPS | RC3  | — B C | — B C — — | — B C — — — |
| I 2 C1 Data | I2C1SDAPPS | RC4  | — B C | — B C — — | — B C — — — |
| I 2 C2 Clock | I2C2SCLPPS | RB1  | — B C | — B — D — | — B — D — — |
| I 2 C2 Data | I2C2SDAPPS | RB2  | — B C | — B — D — | — B — D — — |
| UART1 Receive | U1RXPPS | RC7  | — B C | — B C — — | — — C — — F |
| UART1 Clear To Send | U1CTSPPS | RC6  | — B C | — B C — — | — — C — — F |
| UART2 Receive | U2RXPPS | RB7  | — B C | — B — D — | — B — D — — |
| UART2 Clear To Send | U2CTSPPS | RB6  | — B C | — B — D — | — B — D — — |

# Outputs:

| RxyPPS | Peripheral | 28pin | 40pin | 48pin |
| - | :- | -: | :-: | :-: |
| 0b110010 | ADGRDB | A — C | A — C — — | A — — — — F |
| 0b110001 | ADGRDA | A — C | A — C — — | A — — — — F |
| 0b110000 | CWG3D | A — C | A — — D — | A — — D — — |
| 0b101111 | CWG3C | A — C | A — — D — | A — — D — — |
| 0b101110 | CWG3B | A — C | A — — — E | A — — — E — |
| 0b101101 | CWG3A | — B C | — B C — — | — B C — — — |
| 0b101100 | CWG2D | — B C | — B — D — | — B — D — — |
| 0b101011 | CWG2C | — B C | — B — D — | — B — D — — |
| 0b101010 | CWG2B | — B C | — B — D — | — B — D — — |
| 0b101001 | CWG2A | — B C | — B C — — | — B C — — — |
| 0b101000 | DSM1 | A — C | A — — D — | A — — D - — |
| 0b100111 | CLKR | — B C | — B C — — | — B — — E — |
| 0b100110 | NCO1 | A — C | A — — D — | A — — D — — |
| 0b100101 | TMR0 | — B C | — B C — — | — — C — — F |
| 0b100100 | I2C2SDA | — B C | — B — D — | — B — D — — |
| 0b100011 | I2C2SCL | — B C | — B — D — | — B — D — — |
| 0b100010 | I2C1SDA | — B C | — B C — — | — B C — — — |
| 0b100001 | I2C1SCL | — B C | — B C — — | — B C — — — |
| 0b100000 | SPI1SS | A — C | A — — D — | A — — D — — |
| 0b011111 | SPI1SDO | — B C | — B C — — | — B C — — — |
| 0b011110 | SPI1SCK | — B C | — B C — — | — B C — — — |
| 0b011101 | C2OUT | A — C | A — — — E | A — — — E — |
| 0b011100 | C1OUT | A — C | A — — D — | A — — D — — |
| 0b011000 | UART2RTS | — B C | — B — D — | — B — D — — |
| 0b010111 | UART2TXDE | — B C | — B — D — | — B — D — — |
| 0b010110 | UART2TX | — B C | — B — D — | — B — D — — |
| 0b010101 | UART1RTS | — B C | — B C — — | — — C — — F |
| 0b010100 | UART1TXDE | — B C | — B C — — | — — C — — F |
| 0b010011 | UART1TX | — B C | — B C — — | — — C — — F |
| 0b010000 | PWM8 | A — C | A — — D — | A — — D — — |
| 0b001111 | PWM7 | A — C | A — C — — | — — C — — F |
| 0b001110 | PWM6 | A — C | A — — D — | A — — D — — |
| 0b001101 | PWM5 | A — C | A — C — — | A — — — — F |
| 0b001100 | CCP4 | — B C | — B — D — | — B — D — — |
| 0b001011 | CCP3 | — B C | — B — D — | — B — D — — |
| 0b001010 | CCP2 | — B C | — B C — — | — — C — — F |
| 0b001001 | CCP1 | — B C | — B C — — | — — C — — F |
| 0b001000 | CWG1D | — B C | — B — D — | — B — D — — |
| 0b000111 | CWG1C | — B C | — B — D — | — B — D — — |
| 0b000110 | CWG1B | — B C | — B — D — | — B — D — — |
| 0b000101 | CWG1A | — B C | — B C — — | — B C — — — |
| 0b000100 | CLC4OUT | — B C | — B — D — | — B — D — — |
| 0b000011 | CLC3OUT | — B C | — B — D — | — B — D — — |
| 0b000010 | CLC2OUT | A — C | A — C — — | A — — — — F |
| 0b000001 | CLC1OUT | A — C | A — C — — | A — — — — F |
| 0b000000 | LATxy | A B C | A B C D E | A B C D E F |