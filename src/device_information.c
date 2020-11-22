#include "device_information.h"
#include "nonvolatile_memory.h"
#include "pic_family.h"
#include <stdio.h>

/* ************************************************************************** */
/*  Device Information Area addresses

    These addresses are provided by the datasheet and are available in the
    device header file. I chose to copy the values here instead of including
    the device header both to save the ~35k lines of preprocessor expansion, but
    also to be able to choose my own naming scheme to support the READ_CONFIG()
    macro used below.
*/
/* ************************************************************************** */

#if FAMILY_K42
#define MUI_ADDRESS 0x3F0000
#define EUI_ADDRESS 0x3F0010
#define TSLR2_ADDRESS 0x3F0026
#define TSHR2_ADDRESS 0x3F002C
#define FVRA1X_ADDRESS 0x3F0030
#define FVRA2X_ADDRESS 0x3F0032
#define FVRA4X_ADDRESS 0x3F0034
#define FVRC1X_ADDRESS 0x3F0036
#define FVRC2X_ADDRESS 0x3F0038
#define FVRC4X_ADDRESS 0x3F003A
#else
#define MUI_ADDRESS 0x2C0000
#define EUI_ADDRESS 0x2C0010
#define TSLR2_ADDRESS 0x2C0026
#define TSHR2_ADDRESS 0x2C002C
#define FVRA1X_ADDRESS 0x2C0030
#define FVRA2X_ADDRESS 0x2C0032
#define FVRA4X_ADDRESS 0x2C0034
#define FVRC1X_ADDRESS 0x2C0036
#define FVRC2X_ADDRESS 0x2C0038
#define FVRC4X_ADDRESS 0x2C003A
#endif

device_information_t DIA;

/* -------------------------------------------------------------------------- */

#if FAMILY_K42
#define ERSIZ_ADDRESS 0x3FFF00
#define WLSIZ_ADDRESS 0x3FFF02
#define URSIZ_ADDRESS 0x3FFF04
#define EESIZ_ADDRESS 0x3FFF06
#define PCNT_ADDRESS 0x3FFF08
#else
#define ERSIZ_ADDRESS 0x3C0000
#define WLSIZ_ADDRESS 0x3C0002
#define URSIZ_ADDRESS 0x3C0004
#define EESIZ_ADDRESS 0x3C0006
#define PCNT_ADDRESS 0x3C0008
#endif

device_configuration_t DCI;

/* ************************************************************************** */

// this macro helps streamline grabbing the DIA values
#define READ_CONFIG(area, register)                                            \
    do {                                                                       \
        for (uint8_t i = 0; i < register##_SIZE; i++) {                        \
            area.register##_bytes[i] = flash_read_byte(register##_ADDRESS + i);       \
        }                                                                      \
    } while (0)

/* -------------------------------------------------------------------------- */

char hexMUI[(MUI_SIZE * 2) + 1] = {0};

void device_information_init(void) {
    // Device Information
    READ_CONFIG(DIA, MUI);
    READ_CONFIG(DIA, EUI);
    READ_CONFIG(DIA, TSLR2);
    READ_CONFIG(DIA, TSHR2);
    READ_CONFIG(DIA, FVRA1X);
    READ_CONFIG(DIA, FVRA2X);
    READ_CONFIG(DIA, FVRA4X);
    READ_CONFIG(DIA, FVRC1X);
    READ_CONFIG(DIA, FVRC2X);
    READ_CONFIG(DIA, FVRC4X);

    // Device Configuration
    READ_CONFIG(DCI, ERSIZ);
    READ_CONFIG(DCI, WLSIZ);
    READ_CONFIG(DCI, URSIZ);
    READ_CONFIG(DCI, EESIZ);
    READ_CONFIG(DCI, PCNT);

    // package up the MUI for public consumption
    for (uint8_t i = 0, j = 0; i < (MUI_SIZE / 2); i++, j += 4) {
        sprintf(&hexMUI[j], "%04x", DIA.MUI[i]);
    }
}