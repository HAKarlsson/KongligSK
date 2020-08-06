#include "csr.h"

.global _start
.extern __global_pointer$
.extern _sp
.extern 

_start:
    /* disable interrupts */
    csrw    CSR_MIE, zero
    csrw    CSR_MIP, zero
    fence.i

    /* load gp and sp */
.option push
.option norelax
    la      gp, __global_pointer$
.option pop
    la      sp, _sp

/* initialize the kernel */
    jal     init_kernel

/* setup trap handler */
    la      t0, trap_entry
    /* mtvec mode must be 0. If not zero, hang. */
    andi    t1, t0, 0x3
1:  bnez    t1, 1b
    csrw    mtvec, t0

/* load user context */
    j       restore_user_context
