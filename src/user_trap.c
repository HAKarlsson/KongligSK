#include "user_trap.h"
pcb_t* handle_user_excpt(pcb_t* pcb, uintptr_t mcause, uintptr_t mtval) {
    /* Save user pc. */
    pcb->tr[TR_UEPC] = pcb->gr[GR_PC];
    /* Save trap information. */
    pcb->tr[TR_UCAUSE] = mcause;
    pcb->tr[TR_UTVAL] = mtval;
    /* Disable interrupts and set UPIE if UIE */
    pcb->tr[TR_USTATUS] = (pcb->tr[TR_USTATUS] & 1) << 4;
    /* Jump to trap handler. */
    pcb->gr[GR_PC] = pcb->tr[TR_UTVEC] & ~3UL;
    return pcb;
}

