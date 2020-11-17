#ifndef _PIC_FAMILY_H_
#define _PIC_FAMILY_H_

#define FAMILY_K42                                                             \
    defined(_18F24K42) || defined(_18F25K42) || defined(_18F26K42) ||          \
        defined(_18F27K42) || defined(_18F45K42) || defined(_18F46K42) ||      \
        defined(_18F47K42) || defined(_18F55K42) || defined(_18F56K42) ||      \
        defined(_18F57K42) || defined(_18LF24K42) || defined(_18LF25K42) ||    \
        defined(_18LF26K42) || defined(_18LF27K42) || defined(_18LF45K42) ||   \
        defined(_18LF46K42) || defined(_18LF47K42) || defined(_18LF55K42) ||   \
        defined(_18LF56K42) || defined(_18LF57K42)

#define FAMILY_Q43                                                             \
    defined(_18F25Q43) || defined(_18F26Q43) || defined(_18F27Q43) ||          \
        defined(_18F45Q43) || defined(_18F46Q43) || defined(_18F47Q43) ||      \
        defined(_18F55Q43) || defined(_18F56Q43) || defined(_18F57Q43)

#define FAMILY_Q84                                                             \
    defined(_18F26Q84) || defined(_18F27Q84) || defined(_18F46Q84) ||          \
        defined(_18F47Q84) || defined(_18F56Q84) || defined(_18F57Q84)

#endif