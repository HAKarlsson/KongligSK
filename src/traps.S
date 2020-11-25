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
#include "util.h"

.extern __global_pointer$
.extern handle_trap

.global trap_entry
.global trap_exit

.section .text.traps
.align 4
trap_entry:
    /* Swap tp, with partition pointer. */
    csrrw   a0, mscratch, a0 
    /* Save ra, sp, gp, a0-a7. */
    SREG    ra,  (1 * REGBYTES)(a0)
    SREG    sp,  (2 * REGBYTES)(a0)
    SREG    gp,  (3 * REGBYTES)(a0)
    SREG    a1, (11 * REGBYTES)(a0)
    SREG    a2, (12 * REGBYTES)(a0)
    SREG    a3, (13 * REGBYTES)(a0)
    SREG    a4, (14 * REGBYTES)(a0)
    SREG    a5, (15 * REGBYTES)(a0)
    SREG    a6, (16 * REGBYTES)(a0)
    SREG    a7, (17 * REGBYTES)(a0)

    /* Save pc, a0. */
    csrr    a1, mepc
    csrr    a2, mscratch
    SREG    a1,  (0 * REGBYTES)(a0)
    SREG    a2,  (10 * REGBYTES)(a0)


    /* Load kernel gp, sp. */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_pointer$

    csrr    a1, mcause  /* a1 -> mcause */
    csrr    a2, mtval   /* a2 -> mtval */

    /* trap_handler(part, mcause, mtval) */
    call    trap_handler

trap_exit:
    /* mscratch -> new_part */
    csrw    mscratch, a0
    /* Load pc. */
    LREG    a0,  (0 * REGBYTES)(a0)
    csrw    mepc, a0
    /* Load ra, sp, gp, a1-a7. */
    LREG    ra,  (1 * REGBYTES)(a0)
    LREG    sp,  (2 * REGBYTES)(a0)
    LREG    gp,  (3 * REGBYTES)(a0)
    LREG    a1, (11 * REGBYTES)(a0)
    LREG    a2, (12 * REGBYTES)(a0)
    LREG    a3, (13 * REGBYTES)(a0)
    LREG    a4, (14 * REGBYTES)(a0)
    LREG    a5, (15 * REGBYTES)(a0)
    LREG    a6, (16 * REGBYTES)(a0)
    LREG    a7, (17 * REGBYTES)(a0)
    /* Load a0. */
    LREG    a0, (10 * REGBYTES)(a0)
    /* Return to user context. */
    mret
