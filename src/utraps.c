// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "utraps.h"

#include "csr.h"
#include "defs.h"

void handle_utrap(word_t mcause, word_t mtval) {
    // Save trap information.
    current->ut_regs.ucause = mcause;
    current->ut_regs.utval = mtval;

    // Disable interrupts and set UPIE if UIE.
    current->ut_regs.ustatus = (current->ut_regs.ustatus & 1) << 4;

    // User jumps to trap handler.
    current->ut_regs.uepc = current->regs.pc;

    // Set the trap pc base address
    word_t utvec = current->ut_regs.utvec;
    word_t trap_pc = (utvec & ~0x3);

    // If interrupt and vectored mode, add offset.
    word_t mask = ((long)mcause >> (REGBITS - 1)) & -(long)(utvec & 1);
    trap_pc += (mcause << 2) & mask;

    // Save pc to uepc and jump to trap_pc.
    CSRRW(current->ut_regs.uepc, mepc, trap_pc);
}
