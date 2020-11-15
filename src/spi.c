#include "spi.h"
#include "os/logging.h"
#include "os/system_time.h"
#include "pins.h"
#include "clc.h"
#include "pic_header.h"
#include "pps.h"
static uint8_t LOG_LEVEL = L_SILENT;

/* ************************************************************************** */

void spi_init(pps_output_t *clockOutPin, pps_output_t *dataOutPin) {
    // CLC setup
    clc1_passthrough_init(CLC_SCK1);
    clc2_passthrough_init(CLC_SDO1);

    // PPS setup
    pps_out_CLC1_OUTPUT(clockOutPin);
    pps_out_CLC2_OUTPUT(dataOutPin);

    SPI1CON0bits.BMODE = 1; // Bit-Longth Mode Select

    SPI1CON1bits.CKE = 0;  // Output data changes on transition from
                           // idle to active clock state
    SPI1CON1bits.CKP = 1;  // Idle state for SCK is high level
    SPI1CON1bits.FST = 0;  // Delay to first SCK will be at least ½ baud period
    SPI1CON1bits.SSP = 1;  // SS is active-low
    SPI1CON1bits.SDOP = 0; // SDO is active-low

    SPI1CON2bits.SSET = 0; // SS(out) is driven to the active state while the
                           // transmit counter is not zero
    SPI1CON2bits.TXR = 1;  // TxFIFO data is required for a transfer
    SPI1CON2bits.RXR = 0;  // Received data is not stored in the FIFO

    SPI1BAUD = 7; // Divide the clock source by 16(FOSC/(2*(BAUD+1)))

    SPI1CLK = 0; // FOSC

    SPI1CON0bits.MST = 1; // Set as bus master
    SPI1CON0bits.EN = 1;  // Enable SPI module

    log_register();
}

/* -------------------------------------------------------------------------- */

void spi_tx_word(uint16_t data) {
    LOG_TRACE({ println("spi_tx_word"); });

    // Two byte transfer count
    SPI1TCNTL = 2;
    SPI1TXB = (uint8_t)(data >> 8);   // high byte
    SPI1TXB = (uint8_t)(data & 0xff); // low byte

    while (SPI1STATUSbits.TXBE == 0) {
        // Wait until SPI1TXB is empty
    }

    // TODO: Refactor this as soon as possible
    // FP_STROBE_PIN = 0;
    // delay_us(10);
    // FP_STROBE_PIN = 1;
}

void spi_tx_char(const char data) {
    LOG_TRACE({ println("spi_tx_char"); });
    LOG_DEBUG({ printf("byte: %d", data); });

    // TODO: change this to use the hardware SPI FIFO buffer
    // TODO: consider using a fast_ring_buffer for SPI output, like the UARTs
    while (SPI1STATUSbits.TXBE == 0) {
        // Wait until SPI1TXB is empty
    }

    SPI1TCNTL = 1;
    SPI1TXB = data;
}

void spi_tx_string(const char *string, uint16_t length) {
    LOG_TRACE({ println("spi_tx_string"); });

    for (uint16_t i = 0; i < length; i++) {
        spi_tx_char(string[i]);
    }
}