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

/** TrapEntry(void) 
 * On a user-mode trap, we come to the trap entry.
 * The trap entry must do the following:
 * - Save user context to the PCB.
 * - Load trap handling registers.
 * - Load kernel registers.
 * - Call the kernel body which handles the actual trap.
 */
.align 4 
TrapEntry:
    /* Save user a0, and load pointer to PCB. */
    csrrw   a0, mscratch, a0

    /* Save user context to PCB. */
    sd	    ra, PCB_RA(a0) 
    sd      sp, PCB_SP(a0)  
    sd      gp, PCB_GP(a0)  
    sd      tp, PCB_TP(a0)  
    sd      t0, PCB_T0(a0)  
    sd      t1, PCB_T1(a0)  

    /* Load user a0 and pc. */
    csrr    t0, mscratch    
    csrr    t1, mepc 

    sd	    t2, PCB_T2(a0)  
    sd      s0, PCB_S0(a0)  
    sd      s1, PCB_S1(a0)  
    sd      a1, PCB_A1(a0)  
    sd      a2, PCB_A2(a0)  

    /* Load trap handling registers. */
    csrr    a1, mcause 
    csrr    a2, mtval 

    sd	    a3, PCB_A3(a0)  
    sd      a4, PCB_A4(a0)  
    sd      a5, PCB_A5(a0)  
    sd      a6, PCB_A6(a0)  
    sd      a7, PCB_A7(a0)  
    sd      s2, PCB_S2(a0)  
    sd      s3, PCB_S3(a0)  
    sd      s4, PCB_S4(a0)  
    sd      s5, PCB_S5(a0)  
    sd      s6, PCB_S6(a0)  
    sd      s7, PCB_S7(a0)  
    sd      s8, PCB_S8(a0)  
    sd      s9, PCB_S9(a0)  
    sd      s10, PCB_S10(a0) 
    sd      s11, PCB_S11(a0) 
    sd      t3, PCB_T3(a0)  
    sd      t4, PCB_T4(a0)  
    sd      t5, PCB_T5(a0)  
    sd      t6, PCB_T6(a0)  

    /* Save user a0 and pc. */
    sd	    t0, PCB_A0(a0)
    sd      t1, PCB_PC(a0)

    /* Load kernel gp, sp, and fp. */
    .option push
    .option norelax
    la      gp, __global_pointer$
    .option pop
#if __stack_size > 0
    la      sp, __stack_top
    mv      fp, sp 
#endif
    mv	    s0, a0

    call    TrapHandler 

TrapExit:
    beq	    a0, s0, _skip_pmp
    /* Load PMP settings from memory first. */
    /* We only want to use callee saved regs. */
    ld	    t0, PCB_PMPCFG0(a0)
    ld      t2, PCB_PMPADDR0(a0)
    ld      a1, PCB_PMPADDR1(a0)
    ld      a2, PCB_PMPADDR2(a0)
    ld      a3, PCB_PMPADDR3(a0)
    ld      a4, PCB_PMPADDR4(a0)
    ld      a5, PCB_PMPADDR5(a0)
    ld      a6, PCB_PMPADDR6(a0)
    ld      a7, PCB_PMPADDR7(a0)
    /* Here comes the pipeline flush!!! :/ */
    /* Write to PMP registers. */
    csrw    pmpcfg0, t0
    csrw    pmpaddr0, t2
    csrw    pmpaddr1, a1
    csrw    pmpaddr2, a2
    csrw    pmpaddr3, a3
    csrw    pmpaddr4, a4
    csrw    pmpaddr5, a5
    csrw    pmpaddr6, a6
    csrw    pmpaddr7, a7
_skip_pmp:

    /* We store a pointer to the PCB in MSCRATCH. */
    csrw    mscratch, a0
    /* Load user context from PCB. */
    ld	    t0, PCB_PC(a0)
    ld      ra, PCB_RA(a0)
    ld      sp, PCB_SP(a0)
    ld      gp, PCB_GP(a0)
    ld      tp, PCB_TP(a0)
    csrw    mepc, t0
    ld	    t0, PCB_T0(a0)
    ld      t1, PCB_T1(a0)
    ld      t2, PCB_T2(a0)
    ld      s0, PCB_S0(a0)
    ld      s1, PCB_S1(a0)
    ld      a1, PCB_A1(a0)
    ld      a2, PCB_A2(a0)
    ld      a3, PCB_A3(a0)
    ld      a4, PCB_A4(a0)
    ld      a5, PCB_A5(a0)
    ld      a6, PCB_A6(a0)
    ld      a7, PCB_A7(a0)
    ld      s2, PCB_S2(a0)
    ld      s3, PCB_S3(a0)
    ld      s4, PCB_S4(a0)
    ld      s5, PCB_S5(a0)
    ld      s6, PCB_S6(a0)
    ld      s7, PCB_S7(a0)
    ld      s8, PCB_S8(a0)
    ld      s9, PCB_S9(a0)
    ld      s10, PCB_S10(a0)
    ld      s11, PCB_S11(a0)
    ld      t3, PCB_T3(a0)
    ld      t4, PCB_T4(a0)
    ld      t5, PCB_T5(a0)
    ld      t6, PCB_T6(a0)
    ld      a0, PCB_A0(a0)
    /* Return to user context. */
    mret
