#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/* ************************************************************************** */

/*  Vectored Interrupt Controller

    K42 PICs have a Vectored Interrupt Controller that simplifies ISRs and
    reduces total interrupt latency. Each interrupt source has its own ISR,
    defined using the "Interrupt Source" value from the below table.

    Example: 
    void __interrupt(irq(TMR6), high_priority) example_ISR(void) {
        timer6_IF_clear(); // clear Interrupt Flag

        <ISR body>
    }

    Vector  | Interrupt     | Interrupt Name
    Number  | Source        |
    --------|---------------|---------------------------------------
    0       | IRQ_SWINT     | Software Interrupt 
    1       | IRQ_HLVD      | HLVD Interrupt 
    2       | IRQ_OSF       | Oscillator Failure Interrupt 
    3       | IRQ_CSW       | Clock Switch Interrupt 
    4       | IRQ_NVM       | NVM Interrupt 
    5       | IRQ_SCAN      | Scanner Interrupt 
    6       | IRQ_CRC       | CRC Interrupt 
    7       | IRQ_IOC       | Interrupt on change 
    8       | IRQ_INT0      | External Interrupt 0 
    9       | IRQ_ZCD       | ZCD Interrupt 
    10      | IRQ_AD        | ADC Interrupt 
    11      | IRQ_ADT       | ADC Treshold Interrupt 
    12      | IRQ_CMP1      | Comparator 1 Interrupt 
    13      | IRQ_SMT1      | SMT1 Interrupt 
    14      | IRQ_SMT1PRA   | SMT1 Period acqusition Interrupt 
    15      | IRQ_SMT1PRW   | SMT1 Pulse width acqusition Interrupt 
    16      | IRQ_DMA1SCNT  | DMA1 Source count Interrupt 
    17      | IRQ_DMA1DCNT  | DMA1 Destination count Interrupt 
    18      | IRQ_DMA1OR    | DMA1 Overflow Interrupt 
    19      | IRQ_DMA1A     | DMA1 Abort Interrupt 
    20      | IRQ_SPI1RX    | SPI1 Receive Interrupt 
    21      | IRQ_SPI1TX    | SPI1 Transmit Interrupt 
    22      | IRQ_SPI1      | SPI1 Interrupt 
    23      | IRQ_I2C1RX    | I2C1 Receive Interrupt 
    24      | IRQ_I2C1TX    | I2C1 Transmit Interrupt 
    25      | IRQ_I2C1      | I2C1 Interrupt 
    26      | IRQ_I2C1E     | I2C1 Error Interrupt 
    27      | IRQ_U1RX      | UART1 Receive Interrupt 
    28      | IRQ_U1TX      | UART1 Transmit Interrupt 
    29      | IRQ_U1E       | UART1 Error Interrupt 
    30      | IRQ_U1        | UART1 Interrupt 
    31      | IRQ_TMR0      | Timer0 Interrupt 
    32      | IRQ_TMR1      | Timer1 Interrupt 
    33      | IRQ_TMR1G     | Timer1 Gate Interrupt 
    34      | IRQ_TMR2      | Timer2 Interrupt 
    35      | IRQ_CCP1      | CCP1 Interrupt 
    37      | IRQ_NCO1      | NCO1 Interrupt 
    38      | IRQ_CWG1      | CWG1 Interrupt 
    39      | IRQ_CLC1      | CLC1 Interrupt 
    40      | IRQ_INT1      | External Interrupt 1 
    41      | IRQ_CMP2      | Comparator 2 Interrupt 
    42      | IRQ_DMA2SCNT  | DMA2 Source count Interrupt 
    43      | IRQ_DMA2DCNT  | DMA2 Destination count Interrupt 
    44      | IRQ_DMA2OR    | DMA2 Overflow Interrupt 
    45      | IRQ_DMA2A     | DMA2 Abort Interrupt 
    46      | IRQ_I2C2RX    | I2C2 Receive Interrupt 
    47      | IRQ_I2C2TX    | I2C2 Transmit Interrupt 
    48      | IRQ_I2C2      | I2C2 Interrupt 
    49      | IRQ_I2C2E     | I2C2 Error Interrupt 
    50      | IRQ_U2RX      | UART2 Receive Interrupt 
    51      | IRQ_U2TX      | UART2 Transmit Interrupt 
    52      | IRQ_U2E       | UART2 Error Interrupt 
    53      | IRQ_U2        | UART2 Interrupt 
    54      | IRQ_TMR3      | Timer3 Interrupt 
    55      | IRQ_TMR3G     | Timer3 Gate Interrupt 
    56      | IRQ_TMR4      | Timer4 Interrupt 
    57      | IRQ_CCP2      | CCP2 Interrupt 
    59      | IRQ_CWG2      | CWG2 Interrupt 
    60      | IRQ_CLC2      | CLC2 Interrupt 
    61      | IRQ_INT2      | External Interrupt 2 
    70      | IRQ_TMR5      | Timer5 Interrupt 
    71      | IRQ_TMR5G     | Timer5 Gate Interrupt 
    72      | IRQ_TMR6      | Timer6 Interrupt 
    73      | IRQ_CCP3      | CCP3 Interrupt 
    74      | IRQ_CWG3      | CWG3 Interrupt 
    75      | IRQ_CLC3      | CLC3 Interrupt 
    80      | IRQ_CCP4      | CCP4 Interrupt 
    81      | IRQ_CLC4      | CLC4 Interrupt 
*/

// 
extern void begin_critical_section(void);
extern void end_critical_section(void);

/* -------------------------------------------------------------------------- */

// Clear
extern void interrupt_init(void);

#endif // _INTERRUPT_H_