// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "defs.h"

.extern __global_pointer$
.extern handle_trap

.global trap_entry
.global trap_exit

.section .text.traps
.align 4
trap_entry:
    // Swap user tp with partition pointer.
    csrrw   tp, mscratch, tp 
    // Save user ra, sp, gp, a0-a7.
    SREG    ra,  (1 * REGBYTES)(tp)
    SREG    sp,  (2 * REGBYTES)(tp)
    SREG    gp,  (3 * REGBYTES)(tp)
    SREG    a0, (10 * REGBYTES)(tp)
    SREG    a1, (11 * REGBYTES)(tp)
    SREG    a2, (12 * REGBYTES)(tp)
    SREG    a3, (13 * REGBYTES)(tp)
    SREG    a4, (14 * REGBYTES)(tp)
    SREG    a5, (15 * REGBYTES)(tp)
    SREG    a6, (16 * REGBYTES)(tp)
    SREG    a7, (17 * REGBYTES)(tp)

    // Load kernel gp, sp.
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_pointer$


    // trap_handler(mcause, mtval)
    csrr    a0, mcause
    csrr    a1, mtval
    call    trap_handler

trap_exit:
    // Load user ra, sp, gp, a1-a7.
    LREG    ra,  (1 * REGBYTES)(tp)
    LREG    sp,  (2 * REGBYTES)(tp)
    LREG    gp,  (3 * REGBYTES)(tp)
    LREG    a0, (10 * REGBYTES)(tp)
    LREG    a1, (11 * REGBYTES)(tp)
    LREG    a2, (12 * REGBYTES)(tp)
    LREG    a3, (13 * REGBYTES)(tp)
    LREG    a4, (14 * REGBYTES)(tp)
    LREG    a5, (15 * REGBYTES)(tp)
    LREG    a6, (16 * REGBYTES)(tp)
    LREG    a7, (17 * REGBYTES)(tp)
    // Swap user tp with partition pointer.
    csrrw   tp, mscratch, tp
    // Return to user context.
    mret
