#ifndef _SPI_H_
#define _SPI_H_

#include "pps.h"
#include <stdint.h>

/* ************************************************************************** */

typedef struct {
    pps_output_t *clockOutPin;
    pps_output_t *dataOutPin;
    pps_input_t dataInPin;
} spi_config_t;

// setup
extern void spi1_init(spi_config_t config);

/* -------------------------------------------------------------------------- */

#define MAX_SPI_DEVICES 4

typedef struct {
    struct {
        unsigned useHardware : 1;
        unsigned polarity : 1;
        unsigned enable : 1;
        pps_output_t *pin;
    } slaveSelect;
    unsigned inputPolarity : 1;
    unsigned outputPolarity : 1;

    unsigned bmode : 1;
    uint8_t width;

    void (*prehook)(void);
    void (*posthook)(void);
} spi_device_t;

// register a new device
// returns the deviceID for the new device
extern uint8_t spi1_register_device(spi_device_t device);

/* -------------------------------------------------------------------------- */

//
extern void spi1_exchange_block(uint8_t deviceID, uint8_t *block, uint8_t size);

#endif