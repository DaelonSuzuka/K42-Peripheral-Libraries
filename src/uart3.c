#include "pic_family.h"

/* ************************************************************************** */

#if FAMILY_Q43 || FAMILY_Q84 || FAMILY_Q41

#define UARTX 3
#include "uart_impl.h"
#undef UARTX

#endif