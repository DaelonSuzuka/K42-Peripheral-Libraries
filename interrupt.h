#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/* ************************************************************************** */

// 
extern void begin_critical_section(void);
extern void end_critical_section(void);

/* -------------------------------------------------------------------------- */

extern void interrupt_init(void);

#endif // _INTERRUPT_H_