#include "csr.h"
#include "pcb_offset.h"

.global trap_exit 
.global trap_entry
.extern handle_excpt
.extern handle_intrp

.section .text.traps
/* Trap vector MUST be 4 byte aligned for _DIRECT_ MTVEC mode.*/
.align 4 
/* trap_entry(void) */
trap_entry:
    /* Swap a0 with PCB pointer in MSCRATCH. */
    csrrw   a0, CSR_MSCRATCH, a0

/* 
 * Here we can add checks for exceptions or interrupts in the kernel, 
 * but we assume the kernel is error free and non preemptible. This
 * removes expensive branching.
 */

    /* Save user context to PCB. */
    /* Save general purpose registers. */
    SREG    ra, PCB_RA(a0)  
    SREG    sp, PCB_SP(a0)  
    SREG    gp, PCB_GP(a0)  
    SREG    tp, PCB_TP(a0)  
    SREG    t0, PCB_T0(a0)  
    SREG    t1, PCB_T1(a0)  
    SREG    t2, PCB_T2(a0)  
    SREG    s0, PCB_S0(a0)  
    SREG    s1, PCB_S1(a0)  
    SREG    a1, PCB_A1(a0)  
    SREG    a2, PCB_A2(a0)  
    SREG    a3, PCB_A3(a0)  
    SREG    a4, PCB_A4(a0)  
    SREG    a5, PCB_A5(a0)  
    SREG    a6, PCB_A6(a0)  
    SREG    a7, PCB_A7(a0)  
    SREG    s2, PCB_S2(a0)  
    SREG    s3, PCB_S3(a0)  
    SREG    s4, PCB_S4(a0)  
    SREG    s5, PCB_S5(a0)  
    SREG    s6, PCB_S6(a0)  
    SREG    s7, PCB_S7(a0)  
    SREG    s8, PCB_S8(a0)  
    SREG    s9, PCB_S9(a0)  
    SREG    s10, PCB_S10(a0) 
    SREG    s11, PCB_S11(a0) 
    SREG    t3, PCB_T3(a0)  
    SREG    t4, PCB_T4(a0)  
    SREG    t5, PCB_T5(a0)  
    SREG    t6, PCB_T6(a0)  
    csrr    t0, CSR_MSCRATCH
    SREG    t0, PCB_A0(a0)
    /* Save program counter. */
    csrr    t1, CSR_MEPC
    SREG    t1, PCB_PC(a0)

    /* Call interrupt or exception handler. */
    csrr    a1, CSR_MCAUSE
    csrr    a2, CSR_MTVAL
    bltz    a1, 1f
    /* handle_excpt(pcb_t *pcb, long mcause, long mtval) */
    tail    handle_excpt   
    /* handle_intrp(pcb_t *pcb, long mcause, long mtval) */
1:  tail    handle_intrp
    

/* trap_exit(pcb_t* pcb) */
trap_exit:
    /* We store a pointer to the PCB in MSCRATCH. */
    csrw    CSR_MSCRATCH, a0
    /* Load user context from PCB. */
    /* Restore program counter. */
    LREG    t0, PCB_PC(a0)
    csrw    CSR_MEPC, t0
    /* Restore general purpose registers. */
    LREG    ra, PCB_RA(a0)  
    LREG    sp, PCB_SP(a0)  
    LREG    gp, PCB_GP(a0)  
    LREG    tp, PCB_TP(a0)  
    LREG    t0, PCB_T0(a0)  
    LREG    t1, PCB_T1(a0)  
    LREG    t2, PCB_T2(a0)  
    LREG    s0, PCB_S0(a0)  
    LREG    s1, PCB_S1(a0)  
    LREG    a1, PCB_A1(a0)  
    LREG    a2, PCB_A2(a0)  
    LREG    a3, PCB_A3(a0)  
    LREG    a4, PCB_A4(a0)  
    LREG    a5, PCB_A5(a0)  
    LREG    a6, PCB_A6(a0)  
    LREG    a7, PCB_A7(a0)  
    LREG    s2, PCB_S2(a0)  
    LREG    s3, PCB_S3(a0)  
    LREG    s4, PCB_S4(a0)  
    LREG    s5, PCB_S5(a0)  
    LREG    s6, PCB_S6(a0)  
    LREG    s7, PCB_S7(a0)  
    LREG    s8, PCB_S8(a0)  
    LREG    s9, PCB_S9(a0)  
    LREG    s10, PCB_S10(a0) 
    LREG    s11, PCB_S11(a0) 
    LREG    t3, PCB_T3(a0)  
    LREG    t4, PCB_T4(a0)  
    LREG    t5, PCB_T5(a0)  
    LREG    t6, PCB_T6(a0)  
    LREG    a0, PCB_A0(a0)
    /* Return to user context. */
    mret
