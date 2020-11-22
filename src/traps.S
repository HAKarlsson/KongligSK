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

.global trap_entry
.global trap_exit

.section .text.mentry

/** TrapEntry(void)
 * On a user-mode trap, we come to the trap entry.
 * The trap entry must do the following:
 * - Save user context to the PCB.
 * - Load trap handling registers.
 * - Load kernel registers.
 * - Call the kernel body which handles the actual trap.
 */
.align 4
trap_entry:
    /* Swap tp, with PCB pointer. */
    csrrw   tp, mscratch, tp /* tp -> proc, mscratch -> user tp */
    beqz    tp, __hang

    /* Save callee saved register. */
    sd	    ra, PCB_RA(tp)
    sd	    sp, PCB_SP(tp)
    sd      t0, PCB_T0(tp)
    sd      t1, PCB_T1(tp)
    sd	    t2, PCB_T2(tp)
    sd      t3, PCB_T3(tp)
    sd      t4, PCB_T4(tp)
    sd      t5, PCB_T5(tp)
    sd      t6, PCB_T6(tp)
    sd      a1, PCB_A1(tp)
    sd      a2, PCB_A2(tp)
    sd	    a3, PCB_A3(tp)
    sd      a4, PCB_A4(tp)
    sd      a5, PCB_A5(tp)
    sd      a6, PCB_A6(tp)
    sd      a7, PCB_A7(tp)
    sd      a0, PCB_A0(tp)

    /* Save pc, tp, gp. */
    csrr    t0, mepc
    csrrw   t1, mscratch, zero
    sd      t0, PCB_PC(tp)
    sd	    t1, PCB_TP(tp)
    sd      gp, PCB_GP(tp)


    /* Load kernel gp, sp. */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_top

    /* Call trap_handler(proc, mcause, mtval) */
    mv	    a0, tp	/* a0 -> proc */
    csrr    a1, mcause  /* a1 -> mcause */
    csrr    a2, mtval   /* a2 -> mtval */
    call    trap_handler

    /* a0 -> new_proc, tp -> old_proc */
    /* If new_proc == old_proc, skip. */
    beq	    a0,  tp, __restore_proc

/* Save old proc. */
__save_old:
    /* Save saved registers. */
    sd      s0,   PCB_S0(tp)
    sd      s1,   PCB_S1(tp)
    sd      s2,   PCB_S2(tp)
    sd      s3,   PCB_S3(tp)
    sd      s4,   PCB_S4(tp)
    sd      s5,   PCB_S5(tp)
    sd      s6,   PCB_S6(tp)
    sd      s7,   PCB_S7(tp)
    sd      s8,   PCB_S8(tp)
    sd      s9,   PCB_S9(tp)
    sd      s10, PCB_S10(tp)
    sd      s11, PCB_S11(tp)

/* Load new proc. */
__load_new:
trap_exit: /* a0 -> new_proc */
    /* Set up new PMP. */
    ld	    s0,  PCB_PMPCFG0(a0)
    ld      s1, PCB_PMPADDR0(a0)
    ld      s2, PCB_PMPADDR1(a0)
    ld      s3, PCB_PMPADDR2(a0)
    ld      s4, PCB_PMPADDR3(a0)
    ld      s5, PCB_PMPADDR4(a0)
    ld      s6, PCB_PMPADDR5(a0)
    ld      s7, PCB_PMPADDR6(a0)
    ld      s8, PCB_PMPADDR7(a0)
    csrw    pmpcfg0,  s0
    csrw    pmpaddr0, s1
    csrw    pmpaddr1, s2
    csrw    pmpaddr2, s3
    csrw    pmpaddr3, s4
    csrw    pmpaddr4, s5
    csrw    pmpaddr5, s6
    csrw    pmpaddr6, s7
    csrw    pmpaddr7, s8

    /* Load saved registers. */
    ld      s0,   PCB_S0(a0)
    ld      s1,   PCB_S1(a0)
    ld      s2,   PCB_S2(a0)
    ld      s3,   PCB_S3(a0)
    ld      s4,   PCB_S4(a0)
    ld      s5,   PCB_S5(a0)
    ld      s6,   PCB_S6(a0)
    ld      s7,   PCB_S7(a0)
    ld      s8,   PCB_S8(a0)
    ld      s9,   PCB_S9(a0)
    ld      s10, PCB_S10(a0)
    ld      s11, PCB_S11(a0)

/* Load pc, tp, gp and callee saved registers. */
__restore_proc:
    csrw    mscratch, a0 /* mscratch -> new_proc */

    /* Load pc, tp, gp. */
    ld	    t0, PCB_PC(a0)
    csrw    mepc, t0
    ld	    tp, PCB_TP(a0)
    ld      gp, PCB_GP(a0)

    /* Load callee saved registers. */
    ld      ra, PCB_RA(a0)
    ld      sp, PCB_SP(a0)
    ld	    t0, PCB_T0(a0)
    ld      t1, PCB_T1(a0)
    ld      t2, PCB_T2(a0)
    ld      t3, PCB_T3(a0)
    ld      t4, PCB_T4(a0)
    ld      t5, PCB_T5(a0)
    ld      t6, PCB_T6(a0)
    ld      a1, PCB_A1(a0)
    ld      a2, PCB_A2(a0)
    ld      a3, PCB_A3(a0)
    ld      a4, PCB_A4(a0)
    ld      a5, PCB_A5(a0)
    ld      a6, PCB_A6(a0)
    ld      a7, PCB_A7(a0)
    ld      a0, PCB_A0(a0)
    /* Return to user context. */
    mret

__hang:
    csrr    t0, mepc
    csrr    t1, mcause
    csrr    t2, mtval
    ebreak
    j       __hang
