/* 
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 * 
 * KongligSK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * KongligSK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "csr.h"
#include "gr_offset.h"

.global trap_exit 
.global trap_entry
.extern handle_excpt
.extern handle_intrp
.extern __global_pointer$
.extern _sp

.section .text.entry
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
    SREG    ra, GR_RA(a0)  
    SREG    sp, GR_SP(a0)  
    SREG    gp, GR_GP(a0)  
    SREG    tp, GR_TP(a0)  
    SREG    t0, GR_T0(a0)  
    SREG    t1, GR_T1(a0)  
    SREG    t2, GR_T2(a0)  
    SREG    s0, GR_S0(a0)  
    SREG    s1, GR_S1(a0)  
    SREG    a1, GR_A1(a0)  
    SREG    a2, GR_A2(a0)  
    SREG    a3, GR_A3(a0)  
    SREG    a4, GR_A4(a0)  
    SREG    a5, GR_A5(a0)  
    SREG    a6, GR_A6(a0)  
    SREG    a7, GR_A7(a0)  
    SREG    s2, GR_S2(a0)  
    SREG    s3, GR_S3(a0)  
    SREG    s4, GR_S4(a0)  
    SREG    s5, GR_S5(a0)  
    SREG    s6, GR_S6(a0)  
    SREG    s7, GR_S7(a0)  
    SREG    s8, GR_S8(a0)  
    SREG    s9, GR_S9(a0)  
    SREG    s10, GR_S10(a0) 
    SREG    s11, GR_S11(a0) 
    SREG    t3, GR_T3(a0)  
    SREG    t4, GR_T4(a0)  
    SREG    t5, GR_T5(a0)  
    SREG    t6, GR_T6(a0)  
    csrr    t0, CSR_MSCRATCH
    SREG    t0, GR_A0(a0)
    /* Save program counter. */
    csrr    t1, CSR_MEPC
    SREG    t1, GR_PC(a0)

    /* Load kernel gp and sp. */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, _sp

    /* Set return address (ra) to trap_exit */
    la      ra, trap_exit

    /* 
     * If mcause < 0 (e.g., mcause.msb == 1) 
     * then
     *   jump to handle_intrp(pcb, mcause, mtval)
     * else
     *   jump to handle_excpt(pcb, mcause, mtval)
     */
    csrr    a1, CSR_MCAUSE
    csrr    a2, CSR_MTVAL
    bgez    a1, 1f
    j       handle_intrp  
1:  j       handle_excpt

/* trap_exit(pcb_t* pcb) */
trap_exit:
    /* We store a pointer to the PCB in MSCRATCH. */
    csrw    CSR_MSCRATCH, a0
    /* Load user context from PCB. */
    /* Restore program counter. */
    LREG    t0, GR_PC(a0)
    csrw    CSR_MEPC, t0
    /* Restore general purpose registers. */
    LREG    ra, GR_RA(a0)  
    LREG    sp, GR_SP(a0)  
    LREG    gp, GR_GP(a0)  
    LREG    tp, GR_TP(a0)  
    LREG    t0, GR_T0(a0)  
    LREG    t1, GR_T1(a0)  
    LREG    t2, GR_T2(a0)  
    LREG    s0, GR_S0(a0)  
    LREG    s1, GR_S1(a0)  
    LREG    a1, GR_A1(a0)  
    LREG    a2, GR_A2(a0)  
    LREG    a3, GR_A3(a0)  
    LREG    a4, GR_A4(a0)  
    LREG    a5, GR_A5(a0)  
    LREG    a6, GR_A6(a0)  
    LREG    a7, GR_A7(a0)  
    LREG    s2, GR_S2(a0)  
    LREG    s3, GR_S3(a0)  
    LREG    s4, GR_S4(a0)  
    LREG    s5, GR_S5(a0)  
    LREG    s6, GR_S6(a0)  
    LREG    s7, GR_S7(a0)  
    LREG    s8, GR_S8(a0)  
    LREG    s9, GR_S9(a0)  
    LREG    s10, GR_S10(a0) 
    LREG    s11, GR_S11(a0) 
    LREG    t3, GR_T3(a0)  
    LREG    t4, GR_T4(a0)  
    LREG    t5, GR_T5(a0)  
    LREG    t6, GR_T6(a0)  
    LREG    a0, GR_A0(a0)
    /* Return to user context. */
    mret
