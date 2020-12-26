// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "traps.h"

#include "csr.h"
#include "defs.h"
#include "sched.h"
#include "syscall.h"
#include "utraps.h"

typedef void (*handler_t)(word_t mcause, word_t mtval);

static const handler_t handlers[] = {
    // Execeptions
    [MCAUSE_EXCPT_INSTRUCTION_ADDRESS_MISALIGNED] = handle_utrap,
    [MCAUSE_EXCPT_INSTRUCTION_ACCESS_FAULT] = handle_utrap,
    [MCAUSE_EXCPT_ILLEGAL_INSTRUCTION] = 0,
    [MCAUSE_EXCPT_BREAKPOINT] = handle_utrap,
    [MCAUSE_EXCPT_LOAD_ADDRESS_MISALIGNED] = handle_utrap,
    [MCAUSE_EXCPT_LOAD_ACCESS_FAULT] = handle_utrap,
    [MCAUSE_EXCPT_STORE_ADDRESS_MISALIGNED] = handle_utrap,
    [MCAUSE_EXCPT_STORE_ACCESS_FAULT] = handle_utrap,
    [MCAUSE_EXCPT_USER_ECALL] = handle_syscall,
    [MCAUSE_EXCPT_SUPERVISOR_ECALL] = 0,
    [MCAUSE_EXCPT_MACHINE_ECALL] = 0,
    [MCAUSE_EXCPT_INSTRUCTION_PAGE_FAULT] = 0,
    [MCAUSE_EXCPT_LOAD_PAGE_FAULT] = 0,
    [MCAUSE_EXCPT_STORE_PAGE_FAULT] = 0,
    // Interrupts
    [MCAUSE_INTRP_MACHINE_SOFTWARE | 0x10] = 0,
    [MCAUSE_INTRP_MACHINE_TIMER | 0x10] = handle_mtimer,
    [MCAUSE_INTRP_MACHINE_EXTERN | 0x10] = handle_utrap,
};

void trap_handler(word_t mcause, word_t mtval) {
    // If mcause is interrupt, this should be 0x10 (16),
    // otherwise 0.
    word_t intrp_bit = (mcause >> (REGBITS - 1)) << 4;
    return handlers[mcause | intrp_bit](mcause, mtval);
}
