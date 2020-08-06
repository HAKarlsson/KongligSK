#include "csr.h"

.global restore_user_context

.section .text.trap_exit
restore_user_context:
    /* We store the pointer to the TCB in MSCRATCH. */
    csrr    a0, CSR_MSCRATCH
    /* load register from TCB */
    mret
