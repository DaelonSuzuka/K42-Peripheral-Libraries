# Q43:

# Inputs:

| Peripheral                 | Register       | Default Pin | 28pin |   40pin   |    48pin    |
| -------------------------- | -------------- | ----------- | :---: | :-------: | :---------: |
| Interrupt 0                | INT0PPS        | RB0         | A B — | A B — — — | A B — — — — |
| Interrupt 1                | INT1PPS        | RB1         | A B — | A B — — — | — B — D — — |
| Interrupt 2                | INT2PPS        | RB2         | A B — | A B — — — | — B — — — F |
| Timer0 Clock               | T0CKIPPS       | RA4         | A B — | A B — — — | A — — — — F |
| Timer1 Clock               | T1CKIPPS       | RC0         | A — C | A — C — — | — — C — E — |
| Timer1 Gate                | T1GPPS         | RB5         | — B C | — B C — — | — B C — — — |
| Timer3 Clock               | T3CKIPPS       | RC0         | — B C | — B C — — | — — C — E — |
| Timer3 Gate                | T3GPPS         | RC0         | A — C | A — C — — | A — C — — — |
| Timer5 Clock               | T5CKIPPS       | RC2         | A — C | A — C — — | — — C — E — |
| Timer5 Gate                | T5GPPS         | RB4         | — B C | — B — D — | — B — D — — |
| Timer2 Input               | T2INPPS        | RC3         | A — C | A — C — — | A — C — — — |
| Timer4 Input               | T4INPPS        | RC5         | — B C | — B C — — | — B C — — — |
| Timer6 Input               | T6INPPS        | RB7         | — B C | — B — D — | — B — D — — |
| CCP1                       | CCP1PPS        | RC2         | — B C | — B C — — | — — C — — F |
| CCP2                       | CCP2PPS        | RC1         | — B C | — B C — — | — — C — — F |
| CCP3                       | CCP3PPS        | RB5         | — B C | — B — D — | — B — D — — |
| SMT1 Window                | SMT1WINPPS     | RC0         | — B C | — B C — — | — — C — — F |
| SMT1 Signal                | SMT1SIGPPS     | RC1         | — B C | — B C — — | — — C — — F |
| PWM Input 0                | PWMIN0PPS      | RC2         | — B C | — B C — — | — — C — — F |
| PWM Input 1                | PWMIN1PPS      | RC6         | A — C | A — — — E | A — — — E — |
| PWM1 External Reset Source | PWM1ERSPPS     | RC3         | A — C | A — C — — |  A — C — —  |
| PWM2 External Reset Source | PWM2ERSPPS     | RC5         | A — C | A — C — — | — — C — E — |
| PWM3 External Reset Source | PWM3ERSPPS     | RB7         | — B C | — B — D — | — B — D — — |
| CWG1                       | CWG1PPS        | RB0         | — B C | — B — D — | — B — D — — |
| CWG2                       | CWG2PPS        | RB1         | — B C | — B — D — | — B — D — — |
| CWG3                       | CWG3PPS        | RB2         | — B C | — B — D — | — B — D — — |
| DSM1 Carrier Low           | MD1CARLPPS     | RA3         | A — C | A — — D — | A — — D — — |
| DSM1 Carrier High          | MD1CARHPPS     | RA4         | A — C | A — — D — | A — — D — — |
| DSM1 Source                | MD1SRCPPS      | RA5         | A — C | A — — D — | A — — D — — |
| CLCx Input 1               | CLCIN0PPS      | RA0         | A — C | A — C — — | A — C — — — |
| CLCx Input 2               | CLCIN1PPS      | RA1         | A — C | A — C — — | A — C — — — |
| CLCx Input 3               | CLCIN2PPS      | RB6         | — B C | — B — D — | — B — D — — |
| CLCx Input 4               | CLCIN3PPS      | RB7         | — B C | — B — D — | — B — D — — |
| CLCx Input 5               | CLCIN4PPS      | RA0         | A — C | A — C — — | A — C — — — |
| CLCx Input 6               | CLCIN5PPS      | RA1         | A — C | A — C — — | A — C — — — |
| CLCx Input 7               | CLCIN6PPS      | RB6         | — B C | — B — D — | — B — D — — |
| CLCx Input 8               | CLCIN7PPS      | RB7         | — B C | — B — D — | — B — D — — |
| ADC Conversion Trigger     | ADACTPPS       | RB4         | — B C | — B — D — | — B — D — — |
| SPI1 Clock                 | SPI1SCKPPS     | RC3         | — B C | — B C — — | — B C — — — |
| SPI1 Data                  | SPI1SDIPPS     | RC4         | — B C | — B C — — | — B C — — — |
| SPI1 Slave Select          | SPI1SSPPS      | RA5         | A — C | A — — D — | A — — D — — |
| SPI2 Clock                 | SPI2SCKPPS     | RB3         | — B C | — B — D — | — B — D — — |
| SPI2 Data                  | SPI2SDIPPS     | RB2         | — B C | — B — D — | — B — D — — |
| SPI2 Slave Select          | SPI2SSPPS      | RA4         | A — C | A — — D — | A — — D — — |
| I2C1 Clock                 | I2C1SCLPPS (1) | RC3         | — B C | — B C — — | — B C — — — |
| I2C1 Data                  | I2C1SDAPPS (1) | RC4         | — B C | — B C — — | — B C — — — |
| UART1 Receive              | U1RXPPS        | RC7         | — B C | — B C — — | — — C — — F |
| UART1 Clear to Send        | U1CTSPPS       | RC6         | — B C | — B C — — | — — C — — F |
| UART2 Receive              | U2RXPPS        | RB7         | — B C | — B — D — | — B — D — — |
| UART2 Clear to Send        | U2CTSPPS       | RB6         | — B C | — B — D — | — B — D — — |
| UART3 Receive              | U3RXPPS        | RA7         | A B — | A B — — — | A — — — — F |
| UART3 Clear to Send        | U3CTSPPS       | RA6         | A B — | A B — — — | A — — — — F |
| UART4 Receive              | U4RXPPS        | RB5         | — B C | — B — D — | — B — D — — |
| UART4 Clear to Send        | U4CTSPPS       | RB4         | — B C | — B — D — | — B — D — — |
| UART5 Receive              | U5RXPPS        | RA5         | A — C | A — C — — | A — — — — F |
| UART5 Clear to Send        | U5CTSPPS       | RA4         | A — C | A — C — — | A — — — — F |

# Outputs:

| RxyPPS | Peripheral   | 28pin |   40pin   |    48pin    |
| ------ | :----------- | ----: | :-------: | :---------: |
| 0x45   | ADGRDB       | A — C | A — C — — | A — — — — F |
| 0x44   | ADGRDA       | A — C | A — C — — | A — — — — F |
| 0x43   | DSM1         | A — C | A — — D — | A — — D — — |
| 0x42   | CLKR         | — B C | — B C — — | — B — — E — |
| 0x41   | NCO3         | — B C | — B — — E | — B — — E — |
| 0x40   | NCO2         | — B C | — B — D — | — B — D — — |
| 0x3F   | NCO1         | A — C | A — — D — | A — — D — — |
| 0x39   | TMR0         | — B C | — B C — — | — — C — — F |
| 0x38   | I2C1 SDA (1) | — B C | — B C — — | — B C — — — |
| 0x37   | I2C1 SCL (1) | — B C | — B C — — | — B C — — — |
| 0x36   | SPI2 SS      | A — C | A — — D — | A — — D — — |
| 0x35   | SPI2 SDO     | — B C | — B — D — | — B — D — — |
| 0x34   | SPI2 SCK     | — B C | — B — D — | — B — D — — |
| 0x33   | SPI1 SS      | A — C | A — — D — | A — — D — — |
| 0x32   | SPI1 SDO     | — B C | — B C — — | — B C — — — |
| 0x31   | SPI1 SCK     | — B C | — B C — — | — B C — — — |
| 0x30   | C2OUT        | A — C | A — — — E | A — — — E — |
| 0x2F   | C1OUT        | A — C | A — — D — | A — — D — — |
| 0x2E   | UART5 RTS    | — B C | — B C — — | — — C — — F |
| 0x2D   | UART5 TXDE   | — B C | — B C — — | — — C — — F |
| 0x2C   | UART5 TX     | — B C | — B C — — | — — C — — F |
| 0x2B   | UART4 RTS    | A B — | A — — D — | A — — D — — |
| 0x2A   | UART4 TXDE   | A B — | A — — D — | A — — D — — |
| 0x29   | UART4 TX     | A B — | A — — D — | A — — D — — |
| 0x28   | UART3 RTS    | A B — | A B — — — | A — — — — F |
| 0x27   | UART3 TXDE   | A B — | A B — — — | A — — — — F |
| 0x26   | UART3 TX     | A B — | A B — — — | A — — — — F |
| 0x25   | UART2 RTS    | — B C | — B — D — | — B — D — — |
| 0x24   | UART2 TXDE   | — B C | — B — D — | — B — D — — |
| 0x23   | UART2 TX     | — B C | — B — D — | — B — D — — |
| 0x22   | UART1 RTS    | — B C | — B C — — | — — C — — F |
| 0x21   | UART1 TXDE   | — B C | — B C — — | — — C — — F |
| 0x20   | UART1 TX     | — B C | — B C — — | — — C — — F |
| 0x1D   | PWM3S1P2_OUT | — B C | — B — D — | — B — D — — |
| 0x1C   | PWM3S1P1_OUT | — B C | — B — D — | — B — D — — |
| 0x1B   | PWM2S1P2_OUT | — B C | — B — D — | — B — D — — |
| 0x1A   | PWM2S1P1_OUT | — B C | — B — D — | — B — D — — |
| 0x19   | PWM1S1P2_OUT | — B C | — B C — — | — — C — — F |
| 0x18   | PWM1S1P1_OUT | — B C | — B C — — | — — C — — F |
| 0x17   | CCP3         | — B C | — B — D — | — B — D — — |
| 0x16   | CCP2         | — B C | — B C — — | — — C — — F |
| 0x15   | CCP1         | — B C | — B C — — | — — C — — F |
| 0x14   | CWG3D        | A — C | A — — D — | A — — D — — |
| 0x13   | CWG3C        | A — C | A — — D — | A — — D — — |
| 0x12   | CWG3B        | A — C | A — — — E | A — — — E — |
| 0x11   | CWG3A        | — B C | — B C — — | — B C — — — |
| 0x10   | CWG2D        | — B C | — B — D — | — B — D — — |
| 0x0F   | CWG2C        | — B C | — B — D — | — B — D — — |
| 0x0E   | CWG2B        | — B C | — B — D — | — B — D — — |
| 0x0D   | CWG2A        | — B C | — B C — — | — B C — — — |
| 0x0C   | CWG1D        | — B C | — B — D — | — B — D — — |
| 0x0B   | CWG1C        | — B C | — B — D — | — B — D — — |
| 0x0A   | CWG1B        | — B C | — B — D — | — B — D — — |
| 0x09   | CWG1A        | — B C | — B C — — | — B C — — — |
| 0x08   | CLC8OUT      | — B C | — B — D — | — B — D — — |
| 0x07   | CLC7OUT      | — B C | — B — D — | — B — D — — |
| 0x06   | CLC6OUT      | A — C | A — C — — | A — — — — F |
| 0x05   | CLC5OUT      | A — C | A — C — — | A — — — — F |
| 0x04   | CLC4OUT      | — B C | — B — D — | — B — D — — |
| 0x03   | CLC3OUT      | — B C | — B — D — | — B — D — — |
| 0x02   | CLC2OUT      | A — C | A — C — — | A — — — — F |
| 0x01   | CLC1OUT      | A — C | A — C — — | A — — — — F |
| 0x00   | LATxy        | A B C | A B C D E | A B C D E F |


Q84: