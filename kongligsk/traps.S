// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "defs.h"

.section .text

.global trap_entry
.global trap_exit
.extern __global_pointer$
.extern __stack_pointer$
.extern trap_handler

.align 4
trap_entry:
  // Save registers s0-s11 and tp
  csrrw	tp, mscratch, tp 
  SREG	ra, (RA * REGBYTES)(tp)
  SREG	sp, (SP * REGBYTES)(tp)
  SREG	gp, (GP * REGBYTES)(tp)
  SREG	a0, (A0 * REGBYTES)(tp)
  SREG	a1, (A1 * REGBYTES)(tp)
  SREG	a2, (A2 * REGBYTES)(tp)
  SREG	a3, (A3 * REGBYTES)(tp)
  SREG	a4, (A4 * REGBYTES)(tp)
  SREG	a5, (A5 * REGBYTES)(tp)
  SREG	a6, (A6 * REGBYTES)(tp)
  SREG	a7, (A7 * REGBYTES)(tp)

  // Load kernel gp, sp.
.option push
.option norelax 
  la	gp, __global_pointer$
.option pop
  la	sp, __stack_pointer$
  
  csrr	a0, mcause
  csrr	a1, mtval
  call	trap_handler

trap_exit: 
  LREG	ra, (RA * REGBYTES)(tp)
  LREG	sp, (SP * REGBYTES)(tp)
  LREG	gp, (GP * REGBYTES)(tp)
  LREG	a0, (A0 * REGBYTES)(tp)
  LREG	a1, (A1 * REGBYTES)(tp)
  LREG	a2, (A2 * REGBYTES)(tp)
  LREG	a3, (A3 * REGBYTES)(tp)
  LREG	a4, (A4 * REGBYTES)(tp)
  LREG	a5, (A5 * REGBYTES)(tp)
  LREG	a6, (A6 * REGBYTES)(tp)
  LREG	a7, (A7 * REGBYTES)(tp)
  csrrw	tp, mscratch, tp
  mret
