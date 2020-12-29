// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "defs.h"

.global trap_entry
.global trap_exit

.extern __global_pointer$
.extern __stack_pointer$
.extern trap_handler

.section .text.traps
.align 4
trap_entry:
    // Swap user tp with partition pointer.
    csrrw   tp, mscratch, tp 
    // Save user ra, sp, gp, a0-a7.
    sd	    ra,  (1 * REGBYTES)(tp)
    sd      sp,  (2 * REGBYTES)(tp)
    sd      gp,  (3 * REGBYTES)(tp)
    sd      a0, (10 * REGBYTES)(tp)
    sd      a1, (11 * REGBYTES)(tp)
    sd      a2, (12 * REGBYTES)(tp)
    sd      a3, (13 * REGBYTES)(tp)
    sd      a4, (14 * REGBYTES)(tp)
    sd      a5, (15 * REGBYTES)(tp)
    sd      a6, (16 * REGBYTES)(tp)
    sd      a7, (17 * REGBYTES)(tp)

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
    ld	    ra,  (1 * REGBYTES)(tp)
    ld      sp,  (2 * REGBYTES)(tp)
    ld      gp,  (3 * REGBYTES)(tp)
    ld      a0, (10 * REGBYTES)(tp)
    ld      a1, (11 * REGBYTES)(tp)
    ld      a2, (12 * REGBYTES)(tp)
    ld      a3, (13 * REGBYTES)(tp)
    ld      a4, (14 * REGBYTES)(tp)
    ld      a5, (15 * REGBYTES)(tp)
    ld      a6, (16 * REGBYTES)(tp)
    ld      a7, (17 * REGBYTES)(tp)
    // Swap user tp with partition pointer.
    csrrw   tp, mscratch, tp
    // Return to user context.
    mret
