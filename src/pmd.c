#include "pmd.h"
#include "pic_header.h"

/* ************************************************************************** */

#if FAMILY_K42
void pmd_set(enum pmd_module module, bool state) {
        switch (module) {
            // TODO
        }
}
#endif

/* -------------------------------------------------------------------------- */

#if FAMILY_Q43
void pmd_set(enum pmd_module module, bool state) {
    switch (module) {
    case PMD_SYSC:
        PMD0bits.SYSCMD = state;
        break;
    case PMD_FVR:
        PMD0bits.FVRMD = state;
        break;
    case PMD_HLVD:
        PMD0bits.HLVDMD = state;
        break;
    case PMD_CRC:
        PMD0bits.CRCMD = state;
        break;
    case PMD_SCAN:
        PMD0bits.SCANMD = state;
        break;
    case PMD_CLKR:
        PMD0bits.CLKRMD = state;
        break;
    case PMD_IOC:
        PMD0bits.IOCMD = state;
        break;
    case PMD_SMT1:
        PMD1bits.SMT1MD = state;
        break;
    case PMD_TMR0:
        PMD1bits.TMR0MD = state;
        break;
    case PMD_TMR1:
        PMD1bits.TMR1MD = state;
        break;
    case PMD_TMR2:
        PMD1bits.TMR2MD = state;
        break;
    case PMD_TMR3:
        PMD1bits.TMR3MD = state;
        break;
    case PMD_TMR4:
        PMD1bits.TMR4MD = state;
        break;
    case PMD_TMR5:
        PMD1bits.TMR5MD = state;
        break;
    case PMD_TMR6:
        PMD1bits.TMR6MD = state;
        break;
    case PMD_ACT:
        PMD3bits.ACTMD = state;
        break;
    case PMD_DAC1:
        PMD3bits.DAC1MD = state;
        break;
    case PMD_ADC:
        PMD3bits.ADCMD = state;
        break;
    case PMD_CM2:
        PMD3bits.CM2MD = state;
        break;
    case PMD_CM1:
        PMD3bits.CM1MD = state;
        break;
    case PMD_ZCD:
        PMD3bits.ZCDMD = state;
        break;
    case PMD_CWG3:
        PMD4bits.CWG3MD = state;
        break;
    case PMD_CWG2:
        PMD4bits.CWG2MD = state;
        break;
    case PMD_CWG1:
        PMD4bits.CWG1MD = state;
        break;
    case PMD_DSM1:
        PMD4bits.DSM1MD = state;
        break;
    case PMD_NCO3:
        PMD4bits.NCO3MD = state;
        break;
    case PMD_NCO2:
        PMD4bits.NCO2MD = state;
        break;
    case PMD_NCO1:
        PMD4bits.NCO1MD = state;
        break;
    case PMD_PWM3:
        PMD5bits.PWM3MD = state;
        break;
    case PMD_PWM2:
        PMD5bits.PWM2MD = state;
        break;
    case PMD_PWM1:
        PMD5bits.PWM1MD = state;
        break;
    case PMD_CCP3:
        PMD5bits.CCP3MD = state;
        break;
    case PMD_CCP2:
        PMD5bits.CCP2MD = state;
        break;
    case PMD_CCP1:
        PMD5bits.CCP1MD = state;
        break;
    case PMD_UART5:
        PMD6bits.U5MD = state;
        break;
    case PMD_UART4:
        PMD6bits.U4MD = state;
        break;
    case PMD_UART3:
        PMD6bits.U3MD = state;
        break;
    case PMD_UART2:
        PMD6bits.U2MD = state;
        break;
    case PMD_UART1:
        PMD6bits.U1MD = state;
        break;
    case PMD_SPI2:
        PMD6bits.SPI2MD = state;
        break;
    case PMD_SPI1:
        PMD6bits.SPI1MD = state;
        break;
    case PMD_I2C1:
        PMD6bits.I2C1MD = state;
        break;
    case PMD_CLC8:
        PMD7bits.CLC8MD = state;
        break;
    case PMD_CLC7:
        PMD7bits.CLC7MD = state;
        break;
    case PMD_CLC6:
        PMD7bits.CLC6MD = state;
        break;
    case PMD_CLC5:
        PMD7bits.CLC5MD = state;
        break;
    case PMD_CLC4:
        PMD7bits.CLC4MD = state;
        break;
    case PMD_CLC3:
        PMD7bits.CLC3MD = state;
        break;
    case PMD_CLC2:
        PMD7bits.CLC2MD = state;
        break;
    case PMD_CLC1:
        PMD7bits.CLC1MD = state;
        break;
    case PMD_DMA6:
        PMD8bits.DMA6MD = state;
        break;
    case PMD_DMA5:
        PMD8bits.DMA5MD = state;
        break;
    case PMD_DMA4:
        PMD8bits.DMA4MD = state;
        break;
    case PMD_DMA3:
        PMD8bits.DMA3MD = state;
        break;
    case PMD_DMA2:
        PMD8bits.DMA2MD = state;
        break;
    case PMD_DMA1:
        PMD8bits.DMA1MD = state;
        break;
    }
}
#endif

/* -------------------------------------------------------------------------- */

#if FAMILY_Q84
void pmd_set(enum pmd_module module, bool state) {
        switch (module) {
            // TODO
        }
}
#endif

/* -------------------------------------------------------------------------- */

#if FAMILY_Q41
void pmd_set(enum pmd_module module, bool state) {
        switch (module) {
            // TODO
        }
}
#endif