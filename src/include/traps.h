#ifndef _TRAPS_H
#define _TRAPS_H
#include "pcb.h"
#include "types.h"

extern void trap_entry(void) __attribute__ ((noreturn));
extern void trap_exit(pcb_t *pcb) __attribute__ ((noreturn));
void handle_excpt(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) __attribute__ ((noreturn));
void handle_intrp(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) __attribute__ ((noreturn));
#endif /* _TRAPS_H */
