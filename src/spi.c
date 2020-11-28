#include "spi.h"
#include "os/system_time.h"
#include "pic_header.h"

/* ************************************************************************** */

void spi1_init(spi_config_t config) {
    SPI1CON0bits.BMODE = 1; // Bit-Length Mode Select

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

}

/* ************************************************************************** */

static spi_device_t deviceRegistry[MAX_SPI_DEVICES];
static uint8_t devices = 0;

uint8_t spi1_register_device(spi_device_t device) {
    deviceRegistry[devices] = device;

    return devices++;
}

#define DEVICE deviceRegistry[deviceID]

static void select_device(uint8_t deviceID) {
    if (DEVICE.slaveSelect.useHardware) {
        pps_unlock();
        SPI1CON1bits.SSP = DEVICE.slaveSelect.polarity;
        SPI1CON2bits.SSET = DEVICE.slaveSelect.enable;
        pps_out_SPI1_SS(DEVICE.slaveSelect.pin);
        pps_lock();
    }
}

static void clear_device_selection(uint8_t deviceID) {
    if (DEVICE.slaveSelect.useHardware) {
        pps_unlock();
        pps_out_LATCH(DEVICE.slaveSelect.pin);
        pps_lock();
    }
}

/* -------------------------------------------------------------------------- */

void spi1_exchange_block(uint8_t deviceID, uint8_t *block, uint8_t size) {
    select_device(deviceID);

    if (deviceRegistry[deviceID].prehook) {
        deviceRegistry[deviceID].prehook();
    }

    uint8_t *data = block;
    while (size--) {
        SPI1TCNTL = 1;
        SPI1TXB = *data;
        while (!PIR3bits.SPI1RXIF) {
            // wait for byte to finish
        }

        *data++ = SPI1RXB;
    }

    if (deviceRegistry[deviceID].posthook) {
        deviceRegistry[deviceID].posthook();
    }

    clear_device_selection(deviceID);
}