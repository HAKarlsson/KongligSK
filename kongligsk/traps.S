// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "defs.h"

.section .text

.global trap_entry
.global resume_user 
.extern __global_pointer$
.extern _sp
.extern trap_handler

.align 4
trap_entry:
  csrrw tp, mscratch, tp

  SREG	ra, (RA * REGBYTES)(tp)
  SREG  sp, (SP * REGBYTES)(tp)
  SREG	gp, (GP * REGBYTES)(tp)
  SREG	a0, (A0 * REGBYTES)(tp)
  SREG	a1, (A1 * REGBYTES)(tp)
  SREG	a2, (A2 * REGBYTES)(tp)
  SREG	a3, (A3 * REGBYTES)(tp)
  SREG	a4, (A4 * REGBYTES)(tp)
  SREG	a5, (A5 * REGBYTES)(tp)
  SREG	a6, (A6 * REGBYTES)(tp)
  SREG	a7, (A7 * REGBYTES)(tp)

.option push
.option norelax 
  la 	gp, __global_pointer$
.option pop
  la 	sp, _sp
#ifdef SMP
  // add offset to stack
  csrr  x1, mhartid
  slli 	x1, x1, 7
  add	sp, sp, x1
#endif
  tail	trap_handler

