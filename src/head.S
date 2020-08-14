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
#include "csr.h"

.global _start
.extern __global_pointer$
.extern _sp
.extern 

_start:
    /* disable interrupts */
    csrrw   zero, CSR_MIE, zero
    csrrw   zero, CSR_MIP, zero 
    fence.i

    /* load gp and sp */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, _sp

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
    lw      a0, 0(t0)
    sw      a0, 0(t1)
    addi    t0, t0, 4
    addi    t1, t1, 4
    j       1b 
2:

    /* Zero the bss section */
    la      t1, _bss        /* Start of bss section. */
    la      t2, _ebss       /* End of bss section. */
1:  beq     t1, t1, 2f      /* If _bss == _ebss, zeroing finished. */
    sw      zero, 0(t1)
    addi    t1, t1, 4
    j       1b
2:

/* initialize the kernel */
    /* kernel_init(void) */
    call     kernel_init

hang:
    ebreak
    j       hang
