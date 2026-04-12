# Peripheral Pin Select (PPS)

PPS allows flexible remapping of digital I/O functions on PIC18 Q41/Q43 family microcontrollers (also compatible with K42 family).

## Lock/Unlock Pattern

PPS registers are protected. The system must unlock before configuration and lock afterward:

```c
// During initialization (in project's startup.c)
void startup(void) {
    system_init();   // Each module calls pps_* functions
    os_init();
    application_init();
    pps_lock();      // Lock once, after all modules initialized
}
```

## Input Pin Assignment

```c
// Connect UART RX to a pin (project provides the pin)
pps_in_UART1_RX(PPS_MY_RX_PIN);

// Or pass as argument to peripheral init
void init_uart(pps_input_t rx_pin) {
    pps_in_UART1_RX(rx_pin);
}
```

## Output Pin Assignment

```c
// Assign UART TX output to a pin (project provides the pin)
pps_out_UART1_TX(&MY_TX_PPS_REG);

// Or pass as argument
void init_uart(pps_output_t *tx_pin) {
    pps_out_UART1_TX(tx_pin);
}
```

## PPS_INPUT and PPS_OUTPUT Macros

Project defines pins in `pins.h` (or via code generation):

```c
// Input pin macro expands to port/pin encoding
#define PPS_MY_RX_PIN PPS_INPUT(B, 5)

// Output pin macro returns pointer to RXYPPS register
#define PPS_MY_TX_PIN PPS_OUTPUT(B, 7)
```

## Key Points

- Each module configures its own PPS in its `*_init()` function
- No global PPS configuration file
- Lock prevents accidental reconfiguration at runtime
- All pin definitions come from project, not peripheral library

## Key Files

- `pps/pps_in.c` - Input pin assignment functions
- `pps/pps_out.c` - Output pin assignment functions
- `pps/pps_lock.c` - Lock/unlock functionality