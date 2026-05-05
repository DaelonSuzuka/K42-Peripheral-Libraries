# Peripherals Module Quickstart

Load this file first when working with the peripherals submodule.

## What It Is

Low-level hardware drivers for PIC18 Q41/Q43/Q84/K42. UART, PPS, ADC, SPI, timers, NCO, SMT, NVM, etc.

## Key Rules

- **No project-specific code** — pins configured via PPS macros from project
- **Buffer ownership** — buffers are `static` in project code, not in library
- **Interface structs** — function pointers for mocking and DI
- **FAMILY_* conditionals** — `FAMILY_K42`, `FAMILY_Q41`, `FAMILY_Q43`, `FAMILY_Q84` in `pic_family.h`
- **Adding a FAMILY_* branch is safe** — only affects that chip family
- **Changing shared paths is dangerous** — affects ALL projects using this library

## Design Patterns

### Register Wrappers

Peripheral headers (timer.h, adc.h, nco.h, etc.) wrap raw register names in uniform macros:

```c
// timer.h — hides register naming differences between timers/chips
#define timer4_start() TMR4ON = 1
#define timer4_prescale(value) T4CONbits.CKPS = value
```

Project code calls `timer4_start()`, not `TMR4ON = 1`. If a register name changes between chip families, fix it in the header, not in every project.

**Why macros, not functions:** Timing-critical code (ISR handlers, stopwatch, button scanning) needs single-cycle precision and can't afford function call overhead. If the peripheral is ever used in a timing-sensitive context, it must be a macro.

**Important:** These wrappers make project code chip-agnostic *within PIC18 Q/K families*. They are NOT a hardware abstraction layer for porting to STM32 or other architectures. The abstraction depth is exactly "smooth over register naming differences between PIC18 families" — no more.

### UART Template Pattern

`uart_impl.h` is a C template included once per UART instance:

```c
// uart1.c
#define UARTX 1
#include "uart_impl.h"

// uart2.c
#define UARTX 2
#include "uart_impl.h"
```

This solves C's lack of classes/generics. TX/RX ring buffers, ISR handlers, init, and baud selection are written once and stamp out per-instance via `SHORT()` / `LONG()` macros that generate register names like `U1TXB`, `U2BRG`, etc.

**Why:** Fixing a buffer bug once propagates to all UART instances. No copy-paste divergence.

**Cost:** Only the common denominator of all UARTs fits the template. Advanced modes (CAN, LIN, DMX, 9-bit address) are declared in the API but not fully supported by the shared implementation. Adding chip-specific UART features would require breaking the template pattern.

### UART Object Interface

The `uart_interface_t` struct is a function-pointer table — a C-style vtable:

```c
typedef struct {
    void (*tx_string)(const char *, char);
    void (*tx_char)(char);
    char (*rx_char)(void);
    uint8_t (*rx_available)(void);
    // ...more for 9-bit address mode
} uart_interface_t;
```

Usage pattern (from system.c — the composition root):

```c
uart_config_t config = UART_get_config(2);  // defaults for UART2
config.baud = _1000000;                      // override what you need
config.txPin = PPS_DEBUG_TX_PIN;             // project-specific pins
config.rxPin = PPS_DEBUG_RX_PIN;
create_uart_buffers(debug, config, 255);     // project owns buffers (static in project scope)
serial_port_init(&config);                   // OS module receives the interface
```

The project is the composition root: it creates the config, allocates the buffers, and passes the interface to whichever module needs UART access. Modules call `print()`, `getch()`, etc. without knowing which UART or pins they're using. Total decoupling. But function pointers aren't free on PIC18 — computed `CALL` via indirection table costs more cycles and flash than a direct call. This pattern is fine for UART (called from main loop, ISR uses direct calls internally via ring buffers), but would be wrong for anything called from an ISR or a tight loop. That's why timers are macros, not interface structs.

`pic_family.h` defines `FAMILY_K42`, `FAMILY_Q41`, `FAMILY_Q43`, `FAMILY_Q84`. Use these when behavior differs between chips (like NVM erase block sizing). Adding a new branch is safe; changing shared paths is risky.

### Two Portability Strategies

The library uses two approaches to handle chip differences:

1. **Register-existence `#ifdef`** (preferred): Guard on whether the SFR actually exists. The compiler knows which registers the target chip has. Example from `pps.c`:
```c
#ifdef PPS_NCO3    // NCO3 output exists on this chip?
void pps_out_NCO3(pps_output_t *pin) { *pin = PPS_NCO3; }
#endif
```
No chance of calling a function for a peripheral that doesn't exist. The compiler is the source of truth. Also used in `ports.c` (`#ifdef LATD`).

2. **`FAMILY_*` conditionals**: Guard on chip family when the register exists but has different values/behavior. Example from `nonvolatile_memory.h`:
```c
#if FAMILY_K42 || FAMILY_Q41 || FAMILY_Q43 || FAMILY_Q84
    #define FLASH_ERASE_BLOCKSIZE _FLASH_ERASE_SIZE    // already in bytes
#else
    #define FLASH_ERASE_BLOCKSIZE _FLASH_ERASE_SIZE * 2 // words-to-bytes
#endif
```
Needed when the same register name means different things on different families.

Rule of thumb: if the register simply doesn't exist on some chips, use `#ifdef REGISTER_NAME`. If it exists but behaves differently or has different values, use `FAMILY_*`. These aren't interchangeable — existence and behavior are separate concerns. PPS uses both: `#ifdef` in `pps.c` for function existence, `FAMILY_*` in `pps_values.h` for register values.

## ADC and FVR

The ADC driver is fundamentally an FVR consumer. `adc_init()` enables the FVR immediately. `adc_scale_t` isn't an abstract scale — `_1024mV`/`_2048mV`/`_4096mV` map 1:1 to FVR gain settings, and `_5000mV` means VDD reference. `adc_select_scale()` literally calls `fvr_set_adc_buffer_gain()` at runtime.

`adc_read()` does auto-ranging: starts at 4X FVR gain, drops gain if reading is too low (better resolution), bumps to VDD reference if too high (wider range). Per channel, per reading. The FVR isn't "coupled" to the ADC — it IS the ADC's reference strategy.

## CLC (Configurable Logic Cell)

Programmable logic block — a tiny CPLD fabric on the PIC. 4 selectable data inputs, 4 configurable gates (AND/OR/XOR etc.), polarity control, PPS-routed output. Runs entirely in hardware: configure once, runs autonomously, no CPU.

The "passthrough" init is a hardware signal router: feed a signal in (e.g. UART TX), 4-input AND with all inputs tied together passes it through, output routes via PPS. Connects peripherals to pins (or peripherals to peripherals) without CPU involvement.

**K42 vs Q43/Q41 register interface:** Same logical operation, different access pattern. K42 has dedicated per-CLC registers (`CLC1SEL0`, `CLC2CONbits`). Q43/Q41 uses a shared register set — set `CLCSELECT` to pick which CLC, then write to generic `CLCnSEL0`, `CLCnCONbits`. The wrappers hide this difference.

**Typo:** `clc_passthrought_init()` — consistent in both declaration and definition. Named by the author so all callers use the same spelling. Works fine. Fixing would be a shared-path change affecting all projects.

`spi.c` is a half-implementation. Only send-only (shift register) use has been tested. `spi1_exchange_block()` has blocking busy-wait loops — would need ISR + buffer architecture (like UART) for true bidirectional use. The prehook/posthook device pattern works well for device-specific setup/teardown. The device registry (`spi1_register_device()`) returns an ID for use with `spi1_exchange_block()`.

## FVR Settle Time

Both `fvr_set_adc_buffer_gain()` and `fvr_set_comparator_buffer_gain()` busy-wait on `FVRCONbits.RDY` before returning. The settle time is fast enough that this doesn't cause problems, even when the ADC auto-ranger calls these on every scale change. The blocking is priced in.

## Known Q41 Gaps

These libs were built for K42 first. Q41/Q43 support added incrementally. Untested code paths on non-K42 chips are likely buggy. Always verify family-specific behavior.

### By Severity

**High:**
- `numerically_controlled_oscillator.h`: NCO2/NCO3 function declarations are unguarded — Q41 only has NCO1. However, the `.c` implementations ARE guarded with `#if FAMILY_Q43 || FAMILY_Q84`, so calling nco2/nco3 on Q41 produces a link error, not a silent runtime bug. Fix: add the same `#if` guard to the header declarations.

**Medium:**
- `signal_measurement_timer.h`: `smt_window_input` enum shared across families, includes Q41-absent peripherals (CLC5-8, PWM5-8, CCP4, CMP2)
- `timer_constants.h`: Q41 grouped with Q43/Q84 for Timer1/2 clock sources — gets invalid entries (CLC5-8, NCO2/3, TU16A/B). Needs own branch
- `clc.h`: Q41 in `#else` branch with K42. Some macros reference Q41-absent peripherals (CWG3, PWM8)

**Not actually gaps:**
- `pmd.h/c`: Enum includes Q41-absent peripherals but `pmd_set()` is `// TODO` on Q41 — harmless, no one uses PMD
- `pps.c`: Uses `#ifdef` on register names (e.g. `#ifdef PPS_NCO3`), not FAMILY_*. Compiler is the source of truth — functions for absent peripherals simply don't compile in. Smart approach.
- `device_information.c`: Has K42 vs `#else` address guards for DIA/DCI. Looked risky from header but implementation is correct.
- `ports.c`: Uses `#ifdef LATD`/`TRISD` etc. — same register-existence approach as pps.c

**Fixed:**
- `nonvolatile_memory.h`: `FLASH_ERASE_BLOCKSIZE` was wrong for Q41 (fixed — added Q41 to K42 branch)
- `nonvolatile_memory.c`: `flashBuffer __at(0x2500)` out of Q41 RAM bounds (still open — see lode/todo.md)

## Files We Touch Most

| File | What |
|------|-------|
| `src/uart.c` | UART init dispatch (references all UARTn inits) |
| `src/uart1.c`–`src/uart5.c` | Per-UART implementation |
| `src/adc.c` | ADC conversion and scaling |
| `src/nonvolatile_memory.c` | Flash/EEPROM read/write (flashBuffer bug) |
| `src/pps.c` | Peripheral Pin Select mapping |
| `pic_family.h` | Family detection macros |
| `src/fixed_voltage_reference.c` | FVR for ADC reference |

## Lode Index

- [summary.md](summary.md) — architecture overview
