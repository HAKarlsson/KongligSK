#ifndef _TRAPS_H
#define _TRAPS_H
#include "pcb.h"
#include "types.h"
#include "util.h"

extern void trap_entry(void) NO_RETURN;
extern void trap_exit(pcb_t *pcb) NO_RETURN;
pcb_t* handle_excpt(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval); 
pcb_t* handle_intrp(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval);

#endif /* _TRAPS_H */
