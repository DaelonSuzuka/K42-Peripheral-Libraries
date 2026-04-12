# Peripherals Module Summary

Low-level hardware drivers for PIC18 Q41/Q43 family microcontrollers. Provides abstracted interfaces for UART, PPS, ADC, SPI, timers, NCO, SMT, and other peripherals.

## Design Pattern

All peripherals use **dependency injection** — the peripheral library provides initialization functions and structs, and the project supplies configuration and buffer instances. This keeps peripheral code reusable across projects.

## Directory Structure

```
src/peripherals/
├── uart/           # UART driver with buffer abstraction
├── pps/            # Peripheral Pin Select functions
├── adc/            # Analog-to-digital converter
├── spi/            # SPI master
├── timers/         # Timer configuration
└── ...
```

## Usage Pattern

```c
// 1. Get default config
uart_config_t config = UART_get_config(2);
config.baud = _115200;

// 2. Create buffers in project code
create_uart_buffers(my_uart, config, 128);

// 3. Initialize and get interface
uart_interface_t uart = UART_init(&config);

// 4. Pass to modules that need it
my_module_init(&uart);
```

## Key Principles

- **No project-specific code** — all pins configured via PPS macros passed from project
- **Buffer ownership** — buffers are `static` in project code, not in peripheral library
- **Interface structs** — function pointers allow mocking and dependency injection