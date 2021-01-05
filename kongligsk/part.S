// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "defs.h"

.section .text
.global current_switch
.global current_init

current_switch:
  // Save registers s0-s11, t0-t6, tp, and pc.
  SREG	s0, (S0 * REGBYTES)(tp)
  SREG	s1, (S1 * REGBYTES)(tp)
  SREG	s2, (S2 * REGBYTES)(tp)
  SREG	s3, (S3 * REGBYTES)(tp)
  SREG	s4, (S4 * REGBYTES)(tp)
  SREG	s5, (S5 * REGBYTES)(tp)
  SREG	s6, (S6 * REGBYTES)(tp)
  SREG	s7, (S7 * REGBYTES)(tp)
  SREG	s8, (S8 * REGBYTES)(tp)
  SREG	s9, (S9 * REGBYTES)(tp)
  SREG	s10, (S10 * REGBYTES)(tp)
  SREG	s11, (S11 * REGBYTES)(tp)
  SREG	t0, (T0 * REGBYTES)(tp)
  SREG	t1, (T1 * REGBYTES)(tp)
  SREG	t2, (T2 * REGBYTES)(tp)
  SREG	t3, (T3 * REGBYTES)(tp)
  SREG	t4, (T4 * REGBYTES)(tp)
  SREG	t5, (T5 * REGBYTES)(tp)
  SREG	t6, (T6 * REGBYTES)(tp)
  csrr	t0, mscratch
  SREG	t0, (TP * REGBYTES)(tp)
  csrr	t1, mepc
  SREG	t1, (PC * REGBYTES)(tp)

current_init:
  mv	tp, a0
  // Set PMP
  LREG	s0, (PMPCFG0 * REGBYTES)(tp)
#ifdef RV32
  LREG	s1, (PMPCFG0 * REGBYTES)(tp)
#endif
  LREG	s2, (PMPADDR0 * REGBYTES)(tp)
  LREG	s3, (PMPADDR1 * REGBYTES)(tp)
  LREG	s4, (PMPADDR2 * REGBYTES)(tp)
  LREG	s5, (PMPADDR3 * REGBYTES)(tp)
  LREG	s6, (PMPADDR4 * REGBYTES)(tp)
  LREG	s7, (PMPADDR5 * REGBYTES)(tp)
  LREG	s8, (PMPADDR6 * REGBYTES)(tp)
  LREG	s9, (PMPADDR7 * REGBYTES)(tp)
  csrw	pmpcfg0, s0
#ifdef RV32
  csrw	pmpcfg1, s1
#endif
  csrw	pmpaddr0, s2
  csrw	pmpaddr1, s3
  csrw	pmpaddr2, s4
  csrw	pmpaddr3, s5
  csrw	pmpaddr4, s6
  csrw	pmpaddr5, s7
  csrw	pmpaddr6, s8
  csrw	pmpaddr7, s9

  // Load registers s0-s11, t0-t6, tp, and pc.
  LREG	t0, (TP * REGBYTES)(tp)
  csrw	mscratch, t0
  LREG	t1, (PC * REGBYTES)(tp)
  csrw	mepc, t1
  LREG	s0, (S0 * REGBYTES)(tp)
  LREG	s1, (S1 * REGBYTES)(tp)
  LREG	s2, (S2 * REGBYTES)(tp)
  LREG	s3, (S3 * REGBYTES)(tp)
  LREG	s4, (S4 * REGBYTES)(tp)
  LREG	s5, (S5 * REGBYTES)(tp)
  LREG	s6, (S6 * REGBYTES)(tp)
  LREG	s7, (S7 * REGBYTES)(tp)
  LREG	s8, (S8 * REGBYTES)(tp)
  LREG	s9, (S9 * REGBYTES)(tp)
  LREG	s10, (S10 * REGBYTES)(tp)
  LREG	s11, (S11 * REGBYTES)(tp)
  LREG	t0, (T0 * REGBYTES)(tp)
  LREG	t1, (T1 * REGBYTES)(tp)
  LREG	t2, (T2 * REGBYTES)(tp)
  LREG	t3, (T3 * REGBYTES)(tp)
  LREG	t4, (T4 * REGBYTES)(tp)
  LREG	t5, (T5 * REGBYTES)(tp)
  LREG	t6, (T6 * REGBYTES)(tp)

  ret
