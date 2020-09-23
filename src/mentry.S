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
#include "pcb_offset.h"

.extern __global_pointer$
.extern __stack_top

.global TrapEntry
.global TrapExit 

.align 4 
/** TrapEntry(void) 
 * On a user-mode trap, we come to the trap entry.
 * The trap entry must do the following:
 * - Save user context to the PCB.
 * - Load trap handling registers.
 * - Load kernel registers.
 * - Call the kernel body which handles the actual trap.
 */
TrapEntry:
    /* Save user a0, and load pointer to PCB. */
    csrrw   a0, mscratch, a0

    /* Save user context to PCB. */
    SREG    ra, PCB_RA(a0) 
    SREG    sp, PCB_SP(a0)  
    SREG    gp, PCB_GP(a0)  
    SREG    tp, PCB_TP(a0)  
    SREG    t0, PCB_T0(a0)  
    SREG    t1, PCB_T1(a0)  

    /* Load user a0 and pc. */
    csrr    t0, mscratch    
    csrr    t1, mepc 

    SREG    t2, PCB_T2(a0)  
    SREG    s0, PCB_S0(a0)  
    SREG    s1, PCB_S1(a0)  
    SREG    a1, PCB_A1(a0)  
    SREG    a2, PCB_A2(a0)  

    /* Load trap handling registers. */
    csrr    a1, mcause 
    csrr    a2, mtval 

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

    /* Save user a0 and pc. */
    SREG    t0, PCB_A0(a0)
    SREG    t1, PCB_PC(a0)

    /* Load kernel gp, sp, and fp. */
    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop
    la      sp, __stack_top
    mv      fp, sp 

    call    TrapHandler 

TrapExit:
    /* Load PMP settings from memory first. */
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
    /* Write to PMP registers. */
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

    /* We store a pointer to the PCB in MSCRATCH. */
    csrw    mscratch, a0
    /* Load user context from PCB. */
    LREG    t0, PCB_PC(a0)
    LREG    ra, PCB_RA(a0)
    LREG    sp, PCB_SP(a0)
    LREG    gp, PCB_GP(a0)
    LREG    tp, PCB_TP(a0)
    csrw    mepc, t0
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
