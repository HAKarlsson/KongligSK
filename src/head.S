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
#include "csr.h"

.global _start
.extern __global_pointer$
.extern __stack_top
.extern procs
.extern trap_entry
.extern trap_exit 

.section .text.init
_start:
    /* disable interrupts */
    csrwi   CSR_MIE, 0

    /* load gp, sp and fp */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_top
    la	    t0, trap_entry
    csrw    mtvec, t0
    csrw    mstatus, zero
    la	    a0, procs
    tail    trap_exit
