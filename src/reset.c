#include "reset.h"
#include "os/logging.h"
#include "pic_header.h"
#define LOG_LEVEL L_FATAL

/* ************************************************************************** */

// todo: decide on desired fatal error behaviour

void check_hardware_reset_flags(void) {
    if (PCON0bits.STKOVF == 1) {
        LOG_FATAL({ println("\r\n\r\n>>> Stack Overflow <<<"); });
        while (1) {
            // trap
        }
    }

    if (PCON0bits.STKUNF == 1) {
        LOG_FATAL({ println("\r\n\r\n>>> Stack Underflow <<<"); });
        while (1) {
            // trap
        }
    }

    if (PCON0bits.WDTWV == 0) {
        LOG_FATAL({ println("\r\n\r\n>>> Watchdog Window Violation <<<"); });
        while (1) {
            // trap
        }
    }

    if (PCON0bits.RWDT == 0) {
        LOG_FATAL({ println("\r\n\r\n>>> Watchdog Timer Reset <<<"); });
        while (1) {
            // trap
        }
    }

    if (PCON0bits.RMCLR == 0) {
        LOG_FATAL(println("\r\n\r\n>>> MCLR RESET <<<"););
        while (1) {
            // trap
        }
    }

    if (PCON0bits.RI == 0) {
        LOG_FATAL(println("\r\n\r\n>>> RESET Instruction <<<"););
        while (1) {
            // trap
        }
    }

    // This handler is disabled even in dev, because POR is triggered every boot
    if (PCON0bits.POR == 0) {
        // LOG_FATAL(println("\r\n\r\n>>> Power-on RESET <<<"););
        // while (1) {
        //     // trap
        // }
    }

    // This handler is disabled even in dev, because BOR is triggered every boot
    if (PCON0bits.BOR == 0) {
        // LOG_FATAL(println("\r\n\r\n>>> Brown-out RESET <<<"););
        // while (1) {
        //     // trap
        // }
    }
}