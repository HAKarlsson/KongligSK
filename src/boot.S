// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "defs.h"

.global _start
.extern __global_pointer$
.extern __stack_pointer$
.extern init_kernel 
.extern trap_entry

.section .text.init
_start:
    // Disable interrupts:
    csrwi   mie, 0

    // Load kernel gp, sp.
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la	    sp, __stack_pointer$

    la	    a0, trap_entry
    csrw    mtvec, a0
    csrwi   mstatus, 0

    tail    init_kernel
