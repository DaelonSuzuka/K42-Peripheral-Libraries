#include "reset.h"
#include "pic_header.h"

/* ************************************************************************** */

// todo: decide on desired fatal error behaviour

void check_hardware_reset_flags(void) {
    if (PCON0bits.STKOVF == 1) {
        while (1) {
            // trap
        }
    }

    if (PCON0bits.STKUNF == 1) {
        while (1) {
            // trap
        }
    }

    if (PCON0bits.WDTWV == 0) {
        while (1) {
            // trap
        }
    }

    if (PCON0bits.RWDT == 0) {
        while (1) {
            // trap
        }
    }

    if (PCON0bits.RMCLR == 0) {
        while (1) {
            // trap
        }
    }

    if (PCON0bits.RI == 0) {
        while (1) {
            // trap
        }
    }

    if (PCON0bits.POR == 0) {
        // while (1) {
        //     // trap
        // }
    }

    if (PCON0bits.BOR == 0) {
        // while (1) {
        //     // trap
        // }
    }
}