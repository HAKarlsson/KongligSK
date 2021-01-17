// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "traps.h"

#include "csr.h"
#include "defs.h"
#include "sched.h"
#include "syscall.h"

typedef void (*handler_t)(void);

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

void trap_handler(void) {
	uintptr_t mcause = read_csr(mcause);
	// If mcause is interrupt, this should be 0x10 (16), otherwise 0.
	uintptr_t intrp_bit = (mcause >> (REGBITS - 1)) << 4;
	handlers[mcause | intrp_bit]();
	sched();
}

void handle_utrap(void) {
	uintptr_t mcause = read_csr(mcause);
	uintptr_t mtval = read_csr(mtval);
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

void handle_mtimer(void) {
}
