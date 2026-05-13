#ifndef _DAC_H_
#define _DAC_H_

#include <stdint.h>

/* ************************************************************************** */
/*  DAC Driver — 8-bit hardware DAC + 12-bit virtual DAC with dithering       */
/*                                                                            */
/*  Two interfaces:                                                            */
/*                                                                            */
/*  Raw DAC (8-bit):                                                          */
/*    dac_init()          — Enable DAC hardware output                         */
/*    dac_write(value)    — Write 0–255 directly to DAC register              */
/*    dac_read()          — Read current DAC register value                    */
/*                                                                            */
/*  Virtual DAC (12-bit, Bresenham dithered):                                 */
/*    vdac_init()         — Zero accumulator state (call before timer start)   */
/*    vdac_write(value)   — Set 12-bit target (0–4095)                        */
/*    vdac_read()         — Read current 12-bit target                         */
/*    vdac_service()      — One dither tick; call from Timer ISR at ~1 kHz    */
/*                                                                            */
/*  The ISR owns the hardware DAC register. Application code must call        */
/*  vdac_write() instead of dac_write() whenever dithering is active.         */
/*                                                                            */
/*  Timer setup and ISR registration are the application's responsibility     */
/*  (typically in system.c, alongside other timer ISRs).                       */
/* ************************************************************************** */

/* 12-bit dithered output: maximum value */
#define VDAC_MAX 4095

/* --- Raw DAC (8-bit hardware) --- */

extern void dac_init(void);           // Enable DAC output (OE + EN)
extern void dac_write(uint8_t value); // Write 0–255 to DAC1DATL
extern uint8_t dac_read(void);        // Read DAC1DATL

/* --- Virtual DAC (12-bit dithered) --- */

extern void vdac_init(void);             // Zero accumulator, call before timer start
extern void vdac_write(uint16_t value);  // Set 12-bit target (0–4095)
extern uint16_t vdac_read(void);         // Read current 12-bit target
extern void vdac_service(void);          // One Bresenham tick — call from Timer ISR

#endif // _DAC_H_