#include "ports.h"
#include "pic_header.h"

/* ************************************************************************** */

void port_init(void) {
    // Tri-state control; 0 = output enabled, 1 = output disabled
    // Explicitly disable all outputs
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;
#ifdef TRISD
    TRISD = 0xFF;
#endif
#ifdef TRISE
    TRISE = 0xFF;
#endif
#ifdef TRISF
    TRISF = 0xFF;
#endif

    // Output latch - explicitly drive all outputs low
    LATA = 0;
    LATB = 0;
    LATC = 0;
#ifdef LATD
    LATD = 0;
#endif
#ifdef LATE
    LATE = 0;
#endif
#ifdef LATF
    LATF = 0;
#endif

    // Analog Select; 0 = analog mode is disabled, 1 = analog mode is enabled
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
#ifdef ANSELD
    ANSELD = 0;
#endif
#ifdef ANSELE
    ANSELE = 0;
#endif
#ifdef ANSELF
    ANSELF = 0;
#endif

    // Weak Pull-up; 0 = pull-up disabled, 1 = pull-up enabled
    WPUA = 0;
    WPUB = 0;
    WPUC = 0;
#ifdef WPUD
    WPUD = 0;
#endif
#ifdef WPUE
    WPUE = 0;
#endif
#ifdef WPUF
    WPUF = 0;
#endif

    // Open-Drain Control; 0 = Output drives both high and low, 1 =
    ODCONA = 0;
    ODCONB = 0;
    ODCONC = 0;
#ifdef ODCOND
    ODCOND = 0;
#endif
#ifdef ODCONE
    ODCONE = 0;
#endif
#ifdef ODCONF
    ODCONF = 0;
#endif

    // Slew Rate Control; 0 = maximum slew rate, 1 = limited slew rate
    SLRCONA = 0;
    SLRCONB = 0;
    SLRCONC = 0;
#ifdef SLRCOND
    SLRCOND = 0;
#endif
#ifdef SLRCONE
    SLRCONE = 0;
#endif
#ifdef SLRCONF
    SLRCONF = 0;
#endif

    // Input (Logic) Level Control; 0 = TTL, 1 = Schmitt Trigger
    INLVLA = 0xff;
    INLVLB = 0xff;
    INLVLC = 0xff;
#ifdef INLVLD
    INLVLD = 0xff;
#endif
#ifdef INLVLE
    INLVLE = 0xff;
#endif
#ifdef INLVLF
    INLVLF = 0xff;
#endif
}