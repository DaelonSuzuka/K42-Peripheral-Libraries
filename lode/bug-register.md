# Bug Register

Known defects, latent hazards, and their resolutions. Entries stay here after
fixing (moved to Resolved) so the analysis travels with the code.

## Open

- **uart_impl.h RX ISR error handling**: only parity (`PERIF`) is handled;
  framing (`FERIF`) and RX FIFO overflow flags are ignored. Believed benign on
  the K42/Q41-family UART (unlike the old RCSTA parts, it does not hard-lock on
  overrun), but unverified on the bench.
- **uart_impl.h baud table assumes 64 MHz FOSC**: `baudTable[]` values are only
  correct at 64 MHz HFINTOSC with BRGS=1. No compile-time guard. Same class as
  the `delay_us()` clock dependency noted in project roadmaps.

## Resolved

- **uart_buffer.h: RX overflow silently emptied the buffer** (fixed 2026-07-27).
  `rx_buffer_write()` (ISR side) had no full-check — `rx_buffer_is_full()`
  existed but was commented out, likely triaged out during original driver
  development because an ISR-side *blocking* full-check would deadlock (nothing
  can drain while inside the ISR). On overflow, head wrapped and caught tail,
  after which `is_empty()` read true and the entire backlog vanished at once —
  the failure signature is a *disappeared* frame, not a garbled one, which
  presents as an unreproducible hiccup. Only machine-paced RX can trigger it
  (human typing never will); the CI-V radio link on MC-7300 is the fleet's main
  exposure. Fix: drop-newest — the incoming byte is discarded when full.

- **uart_impl.h: TX full-buffer wait was `delay_ms(20)`** (fixed 2026-07-27).
  Right order of magnitude for an 8-byte buffer at 9600 baud circa the driver's
  creation; 400× oversized at 1 Mbaud, and a 20ms stall inside a cooperative
  superloop blows any 10ms task budget. Also made the peripherals layer include
  `os/system_time.h` — a layering inversion. Fix: tight spin with `TXIE = 1`;
  the TX ISR drains at line rate so the wait is one byte-time at the configured
  baud. The os include is gone with it.

- **uart_impl.h: `_config` stored the caller's config pointer** (fixed
  2026-07-27). Every fleet call site passes a pointer to an init-function local.
  Under XC8's compiled stack those locals aren't popped — they're *overlaid*:
  the linker reassigns the same RAM to other functions' locals once init
  returns. Verified in a live map: `OS_init@config` shared its bytes with
  `civ_send_command` / `meter_calculate_target` locals. Nothing read `_config`
  post-init in current products, but `tx_set_address`/`rx_set_address` write
  through it — the first 9-bit-address product to call those at runtime would
  corrupt whichever locals the linker overlaid that build. Fix: `_config` is now
  a driver-owned struct copied by value at init. Side effect: `UART_init()` no
  longer writes default buffer pointers back into the caller's config.

- **uart.h: `EMPTY_UART_INTERFACE(name)` ignored its argument** (fixed
  2026-07-27). The macro always declared the variable `uart` regardless of the
  name passed. Worked by coincidence — both fleet call sites happened to pass
  `uart`.
