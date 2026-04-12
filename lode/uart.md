# UART Driver

The UART driver uses a dependency injection pattern to decouple shared library code from project-specific UART configuration.

## Interface Pattern

```c
typedef struct {
    void (*tx_string)(const char *, const char);
    void (*tx_char)(char);
    char (*rx_char)(void);
    uint8_t (*rx_available)(void);
    void (*tx_set_address)(uint16_t address);
    void (*rx_set_address)(uint16_t address);
    void (*rx_set_address_mask)(uint16_t mask);
    uart_config_t *config;
} uart_interface_t;
```

## Usage Pattern

```c
// Step 1: Get default config for desired UART (1-5)
uart_config_t config = UART_get_config(2);
config.baud = _115200;
config.txPin = PPS_MY_TX_PIN;  // Project-defined
config.rxPin = PPS_MY_RX_PIN;  // Project-defined

// Step 2: Create buffers (static in project code)
create_uart_buffers(my_uart, config, 255);

// Step 3: Initialize and get interface
uart_interface_t uart = UART_init(&config);

// Step 4: Pass to module that needs it
some_module_init(&uart);
```

## Buffer Macros

```c
create_tx_buffer(name, config, size)   // TX only
create_rx_buffer(name, config, size)   // RX only
create_uart_buffers(name, config, size) // Both TX/RX
```

The macros create static buffer structs with properly sized TX and RX arrays.

## Interface Usage

```c
// In the module receiving the interface
void some_module_init(uart_interface_t *uart) {
    uart->tx_string("Hello", '\0');
    
    if (uart->rx_available()) {
        char c = uart->rx_char();
        // process character
    }
}
```

## Available UARTs

PIC18 Q41/Q43 devices have up to 5 UARTs (UART1-5). Each UART can be independently configured with different baud rates and pins via PPS.

## Empty Interface

A dummy interface is available for modules that need a UART but may not always have one:

```c
EMPTY_UART_INTERFACE(my_uart);  // Creates non-functional interface
```

## Default Buffers

If no buffers are provided, the driver uses a minimal 8-byte default buffer. For production use, always create proper buffers with `create_uart_buffers()`.

## Key Files

- `uart/uart.c` - Main UART implementation
- `uart/uart.h` - Public interface and config types
- `uart/uart_buffer.c` - Circular buffer implementation