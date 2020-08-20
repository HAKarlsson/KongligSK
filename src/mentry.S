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
#include "reg_offset.h"

.extern handle_excpt
.extern handle_intrp
.extern __global_pointer$
.extern __stack_top
.extern kernel

.section .text.trap
.align 4 
/* trap_entry(void) */
.global trap_entry
trap_entry:
    .cfi_startproc /* trap_entry */
    .cfi_undefined ra /*?*/
    /* Swap a0 with PCB pointer in MSCRATCH. */
    csrrw   a0, CSR_MSCRATCH, a0
    /* Save user context to PCB. */
    /* Save general purpose registers. */
    SREG    ra, REG_RA(a0)  
    SREG    sp, REG_SP(a0)  
    SREG    gp, REG_GP(a0)  
    SREG    tp, REG_TP(a0)  
    SREG    t0, REG_T0(a0)  
    SREG    t1, REG_T1(a0)  
    SREG    t2, REG_T2(a0)  
    SREG    s0, REG_S0(a0)  
    SREG    s1, REG_S1(a0)  
    SREG    a1, REG_A1(a0)  
    SREG    a2, REG_A2(a0)  
    SREG    a3, REG_A3(a0)  
    SREG    a4, REG_A4(a0)  
    SREG    a5, REG_A5(a0)  
    SREG    a6, REG_A6(a0)  
    SREG    a7, REG_A7(a0)  
    SREG    s2, REG_S2(a0)  
    SREG    s3, REG_S3(a0)  
    SREG    s4, REG_S4(a0)  
    SREG    s5, REG_S5(a0)  
    SREG    s6, REG_S6(a0)  
    SREG    s7, REG_S7(a0)  
    SREG    s8, REG_S8(a0)  
    SREG    s9, REG_S9(a0)  
    SREG    s10, REG_S10(a0) 
    SREG    s11, REG_S11(a0) 
    SREG    t3, REG_T3(a0)  
    SREG    t4, REG_T4(a0)  
    SREG    t5, REG_T5(a0)  
    SREG    t6, REG_T6(a0)  
    csrr    t0, CSR_MSCRATCH
    SREG    t0, REG_A0(a0)
    /* Save program counter. */
    csrr    t1, CSR_MEPC
    SREG    t1, REG_PC(a0)

    /* Load kernel gp, sp, and fp (s0). */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_top
    mv      s0, sp
    /* load pointer to kernel struct */
    la      a1, kernel

    /* Set return address (ra) to trap_exit */
    la      ra, trap_exit

    /* 
     * If mcause < 0 (e.g., mcause.msb == 1) 
     * then
     *   jump to handle_intrp(pcb, kernel, mcause)
     * else
     *   jump to handle_excpt(pcb, kernel, mcause, mtval)
     */
    csrr    a2, CSR_MCAUSE
    bgez    a2, 1f
    j       handle_intrp  
1:  csrr    a3, CSR_MTVAL
    j       handle_excpt
    .cfi_endproc /* trap_entry */

/* trap_exit(pcb_t* pcb) */
.global trap_exit
trap_exit:
    .cfi_startproc /* trap_exit */
    .cfi_undefined ra
    /* We store a pointer to the PCB in MSCRATCH. */
    csrw    CSR_MSCRATCH, a0
    /* Load user context from PCB. */
    /* Restore program counter. */
    LREG    t0, REG_PC(a0)
    csrw    CSR_MEPC, t0
    /* Restore general purpose registers. */
    LREG    ra, REG_RA(a0)  
    LREG    sp, REG_SP(a0)  
    LREG    gp, REG_GP(a0)  
    LREG    tp, REG_TP(a0)  
    LREG    t0, REG_T0(a0)  
    LREG    t1, REG_T1(a0)  
    LREG    t2, REG_T2(a0)  
    LREG    s0, REG_S0(a0)  
    LREG    s1, REG_S1(a0)  
    LREG    a1, REG_A1(a0)  
    LREG    a2, REG_A2(a0)  
    LREG    a3, REG_A3(a0)  
    LREG    a4, REG_A4(a0)  
    LREG    a5, REG_A5(a0)  
    LREG    a6, REG_A6(a0)  
    LREG    a7, REG_A7(a0)  
    LREG    s2, REG_S2(a0)  
    LREG    s3, REG_S3(a0)  
    LREG    s4, REG_S4(a0)  
    LREG    s5, REG_S5(a0)  
    LREG    s6, REG_S6(a0)  
    LREG    s7, REG_S7(a0)  
    LREG    s8, REG_S8(a0)  
    LREG    s9, REG_S9(a0)  
    LREG    s10, REG_S10(a0) 
    LREG    s11, REG_S11(a0) 
    LREG    t3, REG_T3(a0)  
    LREG    t4, REG_T4(a0)  
    LREG    t5, REG_T5(a0)  
    LREG    t6, REG_T6(a0)  
    LREG    a0, REG_A0(a0)
    /* Return to user context. */
    mret
    .cfi_endproc /* trap_exit */
    .end /* end of assembly */
