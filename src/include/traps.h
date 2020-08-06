#ifndef _TRAPS_H
#define _TRAPS_H
void trap_entry(void) __attribute__ ((noreturn));
void trap_exit(pcb_t *pcb) __attribute__ ((noreturn));
void handle_excpt(pcb_t *pcb, long mcause, long mtval) __attribute__ ((noreturn));
void handle_intrp(pcb_t *pcb, long mcause, long mtval) __attribute__ ((noreturn));
#endif /* _TRAPS_H */
