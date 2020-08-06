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

/* initialize the kernel */
    /* init_kernel(void) */
    jal     init_kernel

