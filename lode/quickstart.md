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

## Known Q41 Gaps

These libs were built for K42 first. Q41/Q43 support added incrementally. Untested code paths on non-K42 chips are likely buggy. Known issues:

- `nonvolatile_memory.c`: `flashBuffer __at(0x2500)` hardcoded for larger chip, out of bounds on Q41
- `nonvolatile_memory.h`: `FLASH_ERASE_BLOCKSIZE` was wrong for Q41 (fixed — added to K42 branch)
- Any code path only tested on K42 is suspect on Q41

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
