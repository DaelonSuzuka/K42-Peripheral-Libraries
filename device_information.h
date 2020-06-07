#ifndef _DEVICE_INFORMATION_H_
#define _DEVICE_INFORMATION_H_

#include <stdint.h>

/* ************************************************************************** */
/*  Device Information Area (DIA)

    K42 family PIC microcontrollers contain a region of flash memory that's
    programmed during manufacturing and read-only any time after. This DIA
    memory contains several interesting features:

        Microchip Unique Identifier
            MUI - 12 Bytes
            A serial number that's unique to the individual processor.
        External Unique Identifier
            EUI - 20 Bytes
            Data provided to Microchip by the customer - currently unused.
        Temperature Indicator ADC reading at @ 90°C (low range setting)
            TSLR2 - 2 Bytes
        Temperature Indicator ADC reading at @ 90°C (high range setting)
            TSHR2 - 2 Bytes
        ADC FVR1 Output voltage for 1x setting (in mV)
            FVRA1X - 2 Bytes
        ADC FVR1 Output Voltage for 2x setting (in mV)
            FVRA2X - 2 Bytes
        ADC FVR1 Output Voltage for 4x setting (in mV)
            FVRA4X - 2 Bytes
        Comparator FVR2 output voltage for 1x setting (in mV)
            FVRC1X - 2 Bytes
        Comparator FVR2 output voltage for 2x setting (in mV)
            FVRC2X - 2 Bytes
        Comparator FVR2 output voltage for 4x setting (in mV)
            FVRC4X - 2 Bytes
*/

// Size of each field, in bytes
#define MUI_SIZE 12
#define EUI_SIZE 20
#define TSLR2_SIZE 2
#define TSHR2_SIZE 2
#define FVRA1X_SIZE 2
#define FVRA2X_SIZE 2
#define FVRA4X_SIZE 2
#define FVRC1X_SIZE 2
#define FVRC2X_SIZE 2
#define FVRC4X_SIZE 2

/* ************************************************************************** */

typedef union {
    struct {
        uint8_t MUI_bytes[MUI_SIZE];
        uint8_t EUI_bytes[EUI_SIZE];
        uint8_t TSLR2_bytes[TSLR2_SIZE];
        uint8_t TSHR2_bytes[TSHR2_SIZE];
        uint8_t FVRA1X_bytes[FVRA1X_SIZE];
        uint8_t FVRA2X_bytes[FVRA2X_SIZE];
        uint8_t FVRA4X_bytes[FVRA4X_SIZE];
        uint8_t FVRC1X_bytes[FVRC1X_SIZE];
        uint8_t FVRC2X_bytes[FVRC2X_SIZE];
        uint8_t FVRC4X_bytes[FVRC4X_SIZE];
    };
    struct {
        uint16_t MUI[MUI_SIZE / 2];
        uint16_t EUI[EUI_SIZE / 2];
        uint16_t TSLR2;
        uint16_t TSHR2;
        uint16_t FVRA1X;
        uint16_t FVRA2X;
        uint16_t FVRA4X;
        uint16_t FVRC1X;
        uint16_t FVRC2X;
        uint16_t FVRC4X;
    };
} device_information_t;

extern device_information_t DIA;

/* -------------------------------------------------------------------------- */
/*  Device Configuration Information (DCI)

    K42 family PIC microcontrollers are factory programmed with a handful of
    data fields describing the capabilities of the device.

        Erase Row Size
            ERSIZ - 2 bytes
        Number of write latches per row
            WLSIZ - 2 bytes
        Number of User Rows
            URSIZ - 2 bytes
        Data EEPROM memory size
            EESIZ - 2 bytes
        Pin Count
            PCNT - 2 bytes
*/

// Size of each field, in bytes
#define ERSIZ_SIZE 2
#define WLSIZ_SIZE 2
#define URSIZ_SIZE 2
#define EESIZ_SIZE 2
#define PCNT_SIZE 2

typedef union {
    struct {
        uint8_t ERSIZ_bytes[ERSIZ_SIZE];
        uint8_t WLSIZ_bytes[WLSIZ_SIZE];
        uint8_t URSIZ_bytes[URSIZ_SIZE];
        uint8_t EESIZ_bytes[EESIZ_SIZE];
        uint8_t PCNT_bytes[PCNT_SIZE];
    };
    struct {
        uint16_t ERSIZ;
        uint16_t WLSIZ;
        uint16_t URSIZ;
        uint16_t EESIZ;
        uint16_t PCNT;
    };
} device_configuration_t;

extern device_configuration_t DCI;

/* ************************************************************************** */

extern char hexMUI[(MUI_SIZE * 2) + 1];

extern void device_information_init(void);

/* ************************************************************************** */

#endif // _DEVICE_INFORMATION_H_