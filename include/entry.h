#ifndef _ENTRY_H
#define _ENTRY_H
#include "pcb.h"
#include "util.h"
void trap_entry(void) NO_RETURN;
void trap_exit(pcb_t *pcb) NO_RETURN;
#endif /* _ENTRY_H */

