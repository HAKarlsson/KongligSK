#ifndef _SYSCALL_H
#define _SYSCALL_H
#include "pcb.h"
#include "types.h"
pcb_t* handle_syscall(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval);
#endif /* _SYSCALL_H */
