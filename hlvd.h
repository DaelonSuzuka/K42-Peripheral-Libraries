#ifndef _HLVD_H_
#define _HLVD_H_

/* ************************************************************************** */
/*  High/Low Voltage Detection Module

    This peripheral is effectively a comparator that's permanently connected to
    the device's VDD(input voltage).

    Its trigger level(called the "trip point") is user programmable, and can be
    set to between 1.90V and 4.65V, with approximately 10% tolerance.

    The interrupt can be triggered when the input voltage(VDD) is either above
    or below the trip point. The datasheet seems to indicate that you can enable
    BOTH outputs at the same time, but that sounds like a silly thing to do.
*/

/* ************************************************************************** */

// Turn the HLVD module on or off
extern void hlvd_enable(void);
extern void hlvd_disable(void);

/* -------------------------------------------------------------------------- */

// Turn the HLVD interrupt source on or off
extern void hlvd_interrupt_enable(void);
extern void hlvd_interrupt_disable(void);

// Clear the HLVD interrupt flag
extern void hlvd_interrupt_clear(void);

/* -------------------------------------------------------------------------- */

typedef enum {
    OFF,
    WHEN_ABOVE,
    WHEN_BELOW,
    BOTH,
} trigger_direction_t;

extern void hlvd_set_trigger_direction(trigger_direction_t direction);

/* -------------------------------------------------------------------------- */

// Possible options for hlvd_set_trip_point()
typedef enum {
    //                   Voltage
    // OPTION VALUE    Min  Typ  Max
    _1v90 = 0b0000, // 1.73 1.90 2.07
    _2v10 = 0b0001, // 1.91 2.10 2.29
    _2v25 = 0b0010, // 2.05 2.25 2.45
    _2v50 = 0b0011, // 2.28 2.50 2.73
    _2v60 = 0b0100, // 2.37 2.60 2.83
    _2v75 = 0b0101, // 2.50 2.75 3.00
    _2v90 = 0b0110, // 2.64 2.90 3.16
    _3v15 = 0b0111, // 2.87 3.15 3.43
    _3v35 = 0b1000, // 3.05 3.35 3.65
    _3v60 = 0b1001, // 3.28 3.60 3.92
    _3v75 = 0b1010, // 3.41 3.75 4.09
    _4v00 = 0b1011, // 3.64 4.00 4.36
    _4v20 = 0b1100, // 3.82 4.20 4.58
    _4v35 = 0b1101, // 3.96 4.35 4.74
    _4v65 = 0b1110, // 4.23 4.65 5.07
} trip_point_t;

// This sets the HLVD trigger threshhold
extern void hlvd_set_trip_point(trip_point_t voltage);

#endif // _HLVD_H_