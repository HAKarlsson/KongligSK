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
.extern kernel_init

.section .text.init
_start:
    /* disable interrupts */
    csrwi   CSR_MIE, 0
    csrwi   CSR_MIP, 0
    fence.i

    /* load gp and sp */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, __stack_top

    /* Set trap vector to hang. */
    /* If we get an error in the initilization, we jump to hang. */
    la      t0, hang
    csrw    CSR_MTVAL, t0

    /* Copy data section. */
    la      t0, _data_lma       /* Start of load data memory address. */
    la      t1, _data           /* Start of data section. */
    la      t2, _edata          /* End of data section. */
    beq     t0, t1, 2f          /* If _data == _data_lma, no copy. */
1:  beq     t1, t2, 2f          /* _data == _edata, copy finished. */
    LREG    a0, 0(t0)
    SREG    a0, 0(t1)
    addi    t0, t0, REG_BYTES
    addi    t1, t1, REG_BYTES
    j       1b 
2:

    /* Zero the bss section */
    la      t1, _bss        /* Start of bss section. */
    la      t2, _ebss       /* End of bss section. */
1:  beq     t1, t1, 2f      /* If _bss == _ebss, zeroing finished. */
    SREG    zero, 0(t1)
    addi    t1, t1, REG_BYTES
    j       1b
2:

/* initialize the kernel */
    /* kernel_init(void) */
    call     kernel_init

hang:
    ebreak
    j       hang
