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
.extern handle_trap

.global trap_entry
.global trap_exit

.section .text.traps
.align 4
trap_entry:
    /* Swap tp, with partition pointer. */
    csrrw   tp, mscratch, tp
    /* Save ra, sp, gp, a0-a7. */
    SREG    ra, PCB_RA(tp)
    SREG    sp, PCB_SP(tp)
    SREG    gp, PCB_GP(tp)
    SREG    a0, PCB_A0(tp)
    SREG    a1, PCB_A1(tp)
    SREG    a2, PCB_A2(tp)
    SREG    a3, PCB_A3(tp)
    SREG    a4, PCB_A4(tp)
    SREG    a5, PCB_A5(tp)
    SREG    a6, PCB_A6(tp)
    SREG    a7, PCB_A7(tp)

    /* Save pc, tp. */
    csrr    a0, mepc
    csrr    a1, mscratch
    SREG    a0, PCB_PC(tp)
    SREG    a1, PCB_TP(tp)


    /* Load kernel gp, sp. */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_pointer$

    /* trap_handler(part, mcause, mtval) */
    mv      a0, tp      /* a0 -> part */
    csrr    a1, mcause  /* a1 -> mcause */
    csrr    a2, mtval   /* a2 -> mtval */
    call    trap_handler

    /* a0 -> new_part, tp -> old_part */
    /* If new_part == old_part, skip. */
    beq     a0, tp, __restore

    /* Save s0-s11, t0-t6. */
    SREG    s0,   PCB_S0(tp)
    SREG    s1,   PCB_S1(tp)
    SREG    s2,   PCB_S2(tp)
    SREG    s3,   PCB_S3(tp)
    SREG    s4,   PCB_S4(tp)
    SREG    s5,   PCB_S5(tp)
    SREG    s6,   PCB_S6(tp)
    SREG    s7,   PCB_S7(tp)
    SREG    s8,   PCB_S8(tp)
    SREG    s9,   PCB_S9(tp)
    SREG    s10, PCB_S10(tp)
    SREG    s11, PCB_S11(tp)
    SREG    t0,   PCB_T0(tp)
    SREG    t1,   PCB_T1(tp)
    SREG    t2,   PCB_T2(tp)
    SREG    t3,   PCB_T3(tp)
    SREG    t4,   PCB_T4(tp)
    SREG    t5,   PCB_T5(tp)
    SREG    t6,   PCB_T6(tp)

trap_exit:
    /* Set up new PMP. */
    LREG    s0, PCB_PMPADDR0(a0)
    LREG    s1, PCB_PMPADDR1(a0)
    LREG    s2, PCB_PMPADDR2(a0)
    LREG    s3, PCB_PMPADDR3(a0)
    LREG    s4, PCB_PMPADDR4(a0)
    LREG    s5, PCB_PMPADDR5(a0)
    LREG    s6, PCB_PMPADDR6(a0)
    LREG    s7, PCB_PMPADDR7(a0)
    LREG    s8,  PCB_PMPCFG0(a0)
#ifdef RV32
    LREG    s9,  PCB_PMPCFG1(a0)
#endif
    csrw    pmpaddr0, s0
    csrw    pmpaddr1, s1
    csrw    pmpaddr2, s2
    csrw    pmpaddr3, s3
    csrw    pmpaddr4, s4
    csrw    pmpaddr5, s5
    csrw    pmpaddr6, s6
    csrw    pmpaddr7, s7
    csrw    pmpcfg0,  s8
#ifdef RV32
    csrw    pmpcfg1, s9
#endif
    /* Load s0-s11, t0-t6. */
    LREG    s0,   PCB_S0(a0)
    LREG    s1,   PCB_S1(a0)
    LREG    s2,   PCB_S2(a0)
    LREG    s3,   PCB_S3(a0)
    LREG    s4,   PCB_S4(a0)
    LREG    s5,   PCB_S5(a0)
    LREG    s6,   PCB_S6(a0)
    LREG    s7,   PCB_S7(a0)
    LREG    s8,   PCB_S8(a0)
    LREG    s9,   PCB_S9(a0)
    LREG    s10, PCB_S10(a0)
    LREG    s11, PCB_S11(a0)
    LREG    t0,   PCB_T0(a0)
    LREG    t1,   PCB_T1(a0)
    LREG    t2,   PCB_T2(a0)
    LREG    t3,   PCB_T3(a0)
    LREG    t4,   PCB_T4(a0)
    LREG    t5,   PCB_T5(a0)
    LREG    t6,   PCB_T6(a0)

/* Load pc, tp, ra, sp, gp, a0-a7. */
__restore:
    /* mscratch -> new_part */
    csrw    mscratch, a0
    /* Load pc, tp. */
    LREG    t0, PCB_PC(a0)
    csrw    mepc, t0
    LREG    tp, PCB_TP(a0)
    /* Load ra, sp, gp, a0-a7. */
    LREG    ra, PCB_RA(a0)
    LREG    sp, PCB_SP(a0)
    LREG    gp, PCB_GP(a0)
    LREG    a1, PCB_A1(a0)
    LREG    a2, PCB_A2(a0)
    LREG    a3, PCB_A3(a0)
    LREG    a4, PCB_A4(a0)
    LREG    a5, PCB_A5(a0)
    LREG    a6, PCB_A6(a0)
    LREG    a7, PCB_A7(a0)
    LREG    a0, PCB_A0(a0)
    /* Return to user context. */
    mret
