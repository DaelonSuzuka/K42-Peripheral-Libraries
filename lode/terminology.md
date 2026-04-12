# Terminology

Domain-specific terms used in the peripherals module.

## Hardware Terms

- **PPS** - Peripheral Pin Select; allows remapping digital I/O functions to different pins
- **UART** - Universal Asynchronous Receiver Transmitter; serial communication peripheral
- **PIC18 Q41** - Microchip microcontroller family with flexible PPS

## Pattern Terms

- **Dependency Injection** - Pattern where configuration and buffers are provided by the project, not created in the library
- **Interface Struct** - Structure of function pointers for hardware abstraction
- **Buffer Ownership** - Buffers are statically allocated in project code, peripheral library just uses them