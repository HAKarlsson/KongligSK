// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "defs.h"

.global _start
.extern __global_pointer$
.extern _sp
.extern trap_entry
.extern init_kernel

.section .text.init, "ax"
_start:
  // Disable interrupts
  csrwi	mie, 0 
  csrwi	mstatus, 0
  
  // Load kernel gp, sp
.option push
.option norelax 
  la	gp, __global_pointer$
.option pop
  la	sp, _sp
#ifdef SMP
  // add offset to stack
  csrr  x1, mhartid
  slli 	x1, x1, 7
  add	sp, sp, x1
#endif
  tail  init_kernel
