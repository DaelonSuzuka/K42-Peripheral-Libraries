#include "oscillator.h"
#include "pic_header.h"

/* ************************************************************************** */

void oscillator_init(osc_settings_t settings) {
    OSCCON1bits.NOSC = settings.source;
    OSCCON1bits.NDIV = settings.divider;

    OSCCON3 = 0x00; // CSWHOLD may proceed; SOSCPWR Low power;
    OSCEN = 0x00;   // MFOEN disabled; LFOEN disabled; ADOEN disabled;
                    // SOSCEN disabled; EXTOEN disabled; HFOEN disabled;
    OSCFRQ = settings.freq;
    OSCTUNE = 0x00; // TUN 0;
}

/* -------------------------------------------------------------------------- */

void internal_oscillator_init(void) {
    osc_settings_t settings = {0};
    settings.source  = HFINTOSC;
    settings.freq    = _64_Mhz;
    settings.divider = _by_1;
    oscillator_init(settings);
}

void external_oscillator_init(void) {
    osc_settings_t settings = {0};
    settings.source  = EXTOSC;
    settings.freq    = _64_Mhz;
    settings.divider = _by_1;
    oscillator_init(settings);
}