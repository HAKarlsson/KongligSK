/* load_pmp(pcb_t* pcb) */
#include "pcb_offset.h"
.section .text
.global load_pmp 
load_pmp:
    /* Load from memory first. */
    /* We only want to use callee saved regs. */
    LREG    t0, PCB_PMPCFG0(a0)
#ifdef RV32
    LREG    t1, PCB_PMPCFG1(a0)
#endif
    LREG    t2, PCB_PMPADDR0(a0)
    LREG    a1, PCB_PMPADDR1(a0)
    LREG    a2, PCB_PMPADDR2(a0)
    LREG    a3, PCB_PMPADDR3(a0)
    LREG    a4, PCB_PMPADDR4(a0)
    LREG    a5, PCB_PMPADDR5(a0)
    LREG    a6, PCB_PMPADDR6(a0)
    LREG    a7, PCB_PMPADDR7(a0)
    /* Here comes the pipeline flush!!! :/ */
    csrw    pmpcfg0, t0
#ifdef RV32
    csrw    pmpcfg1, t1
#endif
    csrw    pmpaddr0, t2
    csrw    pmpaddr1, a1
    csrw    pmpaddr2, a2
    csrw    pmpaddr3, a3
    csrw    pmpaddr4, a4
    csrw    pmpaddr5, a5
    csrw    pmpaddr6, a6
    csrw    pmpaddr7, a7
    ret
.end
