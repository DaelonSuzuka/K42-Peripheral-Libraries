# Q41:

# Inputs:

| Peripheral                 | Register   | 14pin | Ports | 20pin | Ports |
| -------------------------- | ---------- | ----- | ----- | ----- | ----- |
| Interrupt 0                | INT0PPS    | RA2   | A — C | RC0   | A B C |
| Interrupt 1                | INT1PPS    | RA4   | A — C | RC1   | A B C |
| Interrupt 2                | INT2PPS    | RA5   | A — C | RC2   | A B C |
| Timer0 Clock               | T0CKIPPS   | RA2   | A — C | RC5   | A B C |
| Timer1 Clock               | T1CKIPPS   | RA5   | A — C | RC6   | A B C |
| Timer1 Gate                | T1GPPS     | RA4   | A — C | RA4   | A B C |
| Timer3 Clock               | T3CKIPPS   | RC5   | A — C | RC5   | A B C |
| Timer3 Gate                | T3GPPS     | RC4   | A — C | RC4   | A B C |
| Timer2 Input               | T2INPPS    | RA5   | A — C | RA5   | A B C |
| Timer4 Input               | T4INPPS    | RC1   | A — C | RC1   | A B C |
| CCP1                       | CCP1PPS    | RC5   | A — C | RC5   | A B C |
| SMT1 Window                | SMT1WINPPS | RA5   | A — C | RA5   | A B C |
| SMT1 Signal                | SMT1SIGPPS | RC0   | A — C | RA4   | A B C |
| PWM Input 0                | PWMIN0PPS  | RC5   | A — C | RC5   | A B C |
| PWM Input 1                | PWMIN1PPS  | RC3   | A — C | RC3   | A B C |
| PWM1 External Reset Source | PWM1ERSPPS | RA5   | A — C | RA5   | A B C |
| PWM2 External Reset Source | PWM2ERSPPS | RC1   | A — C | RC1   | A B C |
| PWM3 External Reset Source | PWM3ERSPPS | RC2   | A — C | RC2   | A B C |
| CWG1                       | CWG1PPS    | RA2   | A — C | RA2   | A B C |
| DSM1 Carrier Low           | MD1CARLPPS | RC2   | A — C | RC2   | A B C |
| DSM1 Carrier High          | MD1CARHPPS | RC5   | A — C | RC5   | A B C |
| DSM1 Source                | MD1SRCPPS  | RA1   | A — C | RA1   | A B C |
| CLCx Input 1               | CLCIN0PPS  | RC3   | A — C | RA2   | A B C |
| CLCx Input 2               | CLCIN1PPS  | RC4   | A — C | RC3   | A B C |
| CLCx Input 3               | CLCIN2PPS  | RC1   | A — C | RB4   | A B C |
| CLCx Input 4               | CLCIN3PPS  | RA4   | A — C | RB5   | A B C |
| ADC Conversion Trigger     | ADACTPPS   | RC2   | A — C | RC2   | A B C |
| SPI1 Clock                 | SPI1SCKPPS | RC0   | A — C | RB6   | A B C |
| SPI1 Data                  | SPI1SDIPPS | RC1   | A — C | RB4   | A B C |
| SPI1 Client Select         | SPI1SSPPS  | RC3   | A — C | RC6   | A B C |
| SPI2 Clock                 | SPI2SCKPPS | RC4   | A — C | RB7   | A B C |
| SPI2 Data                  | SPI2SDIPPS | RC5   | A — C | RB5   | A B C |
| SPI2 Client Select         | SPI2SSPPS  | RA0   | A — C | RA1   | A B C |
| I2C1 Clock                 | I2C1SCLPPS | RC0   | A — C | RB6   | A B C |
| I2C1 Data                  | I2C1SDAPPS | RC1   | A — C | RB4   | A B C |
| UART1 Receive              | U1RXPPS    | RC5   | A — C | RB5   | A B C |
| UART1 Clear to Send        | U1CTSPPS   | RC4   | A — C | RB7   | A B C |
| UART2 Receive              | U2RXPPS    | RC1   | A — C | RC1   | A B C |
| UART2 Clear to Send        | U2CTSPPS   | RC2   | A — C | RC2   | A B C |
| UART3 Receive              | U3RXPPS    | RA4   | A — C | RC3   | A B C |
| UART3 Clear to Send        | U3CTSPPS   | RA5   | A — C | RC5   | A B C |

# Outputs:

| RxyPPS | Peripheral   | 14pin | 20pin |
| ------ | :----------- | ----: | :---: |
| 0x28   | ADGRDB       | A — C | A B C |
| 0x27   | ADGRDA       | A — C | A B C |
| 0x26   | DSM1         | A — C | A B C |
| 0x25   | CLKR         | A — C | A B C |
| 0x24   | NCO1         | A — C | A B C |
| 0x23   | TMR0         | A — C | A B C |
| 0x22   | I2C1SDA      | A — C | A B C |
| 0x21   | I2C1SCL      | A — C | A B C |
| 0x20   | SPI2SS       | A — C | A B C |
| 0x1F   | SPI2SDO      | A — C | A B C |
| 0x1E   | SPI2SCK      | A — C | A B C |
| 0x1D   | SPI1SS       | A — C | A B C |
| 0x1C   | SPI1SDO      | A — C | A B C |
| 0x1B   | SPI1SCK      | A — C | A B C |
| 0x1A   | C2OUT        | A — C | A B C |
| 0x19   | C1OUT        | A — C | A B C |
| 0x18   | UART3RTS     | A — C | A B C |
| 0x17   | UART3TXDE    | A — C | A B C |
| 0x16   | UART3TX      | A — C | A B C |
| 0x15   | UART2RTS     | A — C | A B C |
| 0x14   | UART2TXDE    | A — C | A B C |
| 0x13   | UART2TX      | A — C | A B C |
| 0x12   | UART1RTS     | A — C | A B C |
| 0x11   | UART1TXDE    | A — C | A B C |
| 0x10   | UART1TX      | A — C | A B C |
| 0x0F   | PWM3S1P2_OUT | A — C | A B C |
| 0x0E   | PWM3S1P1_OUT | A — C | A B C |
| 0x0D   | PWM2S1P2_OUT | A — C | A B C |
| 0x0C   | PWM2S1P1_OUT | A — C | A B C |
| 0x0B   | PWM1S1P2_OUT | A — C | A B C |
| 0x0A   | PWM1S1P1_OUT | A — C | A B C |
| 0x09   | CCP1         | A — C | A B C |
| 0x08   | CWG1D        | A — C | A B C |
| 0x07   | CWG1C        | A — C | A B C |
| 0x06   | CWG1B        | A — C | A B C |
| 0x05   | CWG1A        | A — C | A B C |
| 0x04   | CLC4OUT      | A — C | A B C |
| 0x03   | CLC3OUT      | A — C | A B C |
| 0x02   | CLC2OUT      | A — C | A B C |
| 0x01   | CLC1OUT      | A — C | A B C |
| 0x00   | LATxy        | A — C | A B C |