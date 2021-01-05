// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "utraps.h"

#include "csr.h"
#include "defs.h"

void handle_utrap(uintptr_t mcause, uintptr_t mtval) {
	// Save trap information.
	current->ut_regs.ucause = mcause;
	current->ut_regs.utval = mtval;

	// Disable interrupts and set UPIE if UIE.
	current->ut_regs.ustatus = (current->ut_regs.ustatus & 1) << 4;

	// User jumps to trap handler.
	current->ut_regs.uepc = current->regs.pc;

	// Set the trap pc base address
	uintptr_t utvec = current->ut_regs.utvec;
	uintptr_t trap_pc = (utvec & ~0x3);

	// If interrupt and vectored mode, add offset.
	// mask = 0xFF..F if interrupts are enabled and we have an interrupt else 0x0
	uintptr_t mask = ((long)mcause >> (REGBITS - 1)) & -(long)(utvec & 1);
	trap_pc += (mcause << 2) & mask;

	// Save pc to uepc and jump to trap_pc.
	current->ut_regs.uepc = swap_csr(mepc, trap_pc);
}
