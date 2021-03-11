#ifndef _PIC_FAMILY_H_
#define _PIC_FAMILY_H_

/* ************************************************************************** */
/*  PIC_FAMILY feature selection macros

    This set of peripheral libraries is intended to support a number of modern
    families of PIC18 microcontroller. Generally speaking, the target of these
    libs is PIC18 with the Vectored Interrupt Controller. PICs without the IVT
    are different enough that supporting them isn't worth it.

    Family  | Support
    ----------------------------
    K40     | limited, but K40s are mostly similar to K42s
    K42     | full
    Q43     | full
    Q83     | future, should be mostly compatible with Q43
    Q84     | future, should be mostly compatible with Q43
    Q40     | future
    Q41     | future
*/

/* ************************************************************************** */
// K42

#if defined(_18F24K42) || defined(_18F25K42) || defined(_18F26K42) ||          \
    defined(_18F27K42) || defined(_18F45K42) || defined(_18F46K42) ||          \
    defined(_18F47K42) || defined(_18F55K42) || defined(_18F56K42) ||          \
    defined(_18F57K42) || defined(_18LF24K42) || defined(_18LF25K42) ||        \
    defined(_18LF26K42) || defined(_18LF27K42) || defined(_18LF45K42) ||       \
    defined(_18LF46K42) || defined(_18LF47K42) || defined(_18LF55K42) ||       \
    defined(_18LF56K42) || defined(_18LF57K42)
#define FAMILY_K42 1
#else
#define FAMILY_K42 0
#endif

/* -------------------------------------------------------------------------- */
// Q43

#if defined(_18F25Q43) || defined(_18F26Q43) || defined(_18F27Q43) ||          \
    defined(_18F45Q43) || defined(_18F46Q43) || defined(_18F47Q43) ||          \
    defined(_18F55Q43) || defined(_18F56Q43) || defined(_18F57Q43)
#define FAMILY_Q43 1
#else
#define FAMILY_Q43 0
#endif

/* -------------------------------------------------------------------------- */
// Q84

#if defined(_18F26Q84) || defined(_18F27Q84) || defined(_18F46Q84) ||          \
    defined(_18F47Q84) || defined(_18F56Q84) || defined(_18F57Q84)
#define FAMILY_Q84 1
#else
#define FAMILY_Q84 0
#endif

/* -------------------------------------------------------------------------- */
// Q41

#if defined(_18F06Q41) || defined(_18F16Q41) || defined(_18F04Q41) ||          \
    defined(_18F05Q41) || defined(_18F14Q41) || defined(_18F15Q41)
#define FAMILY_Q41 1
#else
#define FAMILY_Q41 0
#endif

#endif