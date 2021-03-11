#include "uart.h"

/* ************************************************************************** */
// UART dummy functions
void dummy_tx_string(const char *string, const char terminator) {
    // intentionally empty body
}
void dummy_tx_char(char data) {
    // intentionally empty body
}
char dummy_rx_char(void) {
    // intentionally empty body, must return something
    return 0;
}
uint8_t dummy_rx_available(void) {
    // intentionally empty body, must return something
    return 0;
}
void dummy_tx_set_address(uint16_t address) {
    // intentionally empty body
}
void dummy_rx_set_address(uint16_t address) {
    // intentionally empty body
}
void dummy_rx_set_address_mask(uint16_t mask) {
    // intentionally empty body
}

/* ************************************************************************** */

// make sure the linker can find these inits
extern uart_interface_t UART1_init(uart_config_t *config);
extern uart_interface_t UART2_init(uart_config_t *config);
#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
extern uart_interface_t UART3_init(uart_config_t *config);
#elif FAMILY_Q43 || FAMILY_Q84
extern uart_interface_t UART4_init(uart_config_t *config);
extern uart_interface_t UART5_init(uart_config_t *config);
#endif

uart_interface_t UART_init(uart_config_t *config) {
    switch (config->number) {
    case 1:
        return UART1_init(config);
    case 2:
        return UART2_init(config);
#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41
    case 3:
        return UART3_init(config);
#elif FAMILY_Q43 || FAMILY_Q84
    case 4:
        return UART4_init(config);
    case 5:
        return UART5_init(config);
#endif
    }

    uart_interface_t blankInterface = {0};
    return blankInterface;
}