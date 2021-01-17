// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#pragma once
#include "config.h"
#include "csr.h"
#include "defs.h"

typedef unsigned long uintptr_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// General purpose registers.
typedef struct regs {
	uintptr_t pc;					     // pc
	uintptr_t ra, sp;				     // x1-x2
	uintptr_t gp, tp;				     // x3-x4
	uintptr_t t0, t1, t2;				     // x5-x7
	uintptr_t s0, s1;				     // x8-x9
	uintptr_t a0, a1;				     // x10-x11
	uintptr_t a2, a3, a4, a5, a6, a7;		     // x12-x17
	uintptr_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;  // x18-x27
	uintptr_t t3, t4, t5, t6;			     // x28-x31
} regs_t;

// User trap setup and handling registers.
typedef struct ut_regs {
	uintptr_t ustatus, uie, utvec;
	uintptr_t uscratch, uepc, ucause, utval, uip;
} ut_regs_t;

// Physical memory protection registers.
typedef struct pmp {
	uint32_t cfg0;
	uint32_t cfg1;
	uintptr_t addr0;
	uintptr_t addr1;
	uintptr_t addr2;
	uintptr_t addr3;
	uintptr_t addr4;
	uintptr_t addr5;
	uintptr_t addr6;
	uintptr_t addr7;
} pmp_t;

// Partition control block.
typedef struct part {
	regs_t regs;
	pmp_t pmp;
	ut_regs_t ut_regs;
	uintptr_t id;
} part_t __attribute__((aligned(16)));

/*
 * An array of partitions.
 */
extern part_t parts[NR_PARTS];

/*
 * Pointer to the current active partition.
 *
 * The register values s0-s11, t0-t6, and pc of an active partition are in
 * context, so the kernel must only use registers ra, sp, gp, tp and a0-a7 to
 * not overwrite the partitions values.  This allows the kernel to have faster
 * system calls since it does not have to save registers s0-s11 and t0-t6 to
 * memory during a system call. This does, however, mean that the kernel must
 * be leaner since it has fewer registers available. Moreover, the PMP settings
 * of the current partition are also loaded.
 */
register part_t *current __asm__("tp");	 // thread pointer points to active partition

/*
 * Switch active partition.
 *
 * Saves the registers s0-s11, t0-t6, tp, and pc of the current partition. Then
 * brings the new partition's PMP configuration and registers s0-s11, t0-t6,
 * tp, and pc into context.
 */
void current_switch(part_t *part);

/*
 * Initialize active partition.
 *
 * Brings the first partition's PMP configuration and registers s0-s11, t0-t6,
 * tp, and pc into context. In the beginning, no partition is loaded, this
 * function is only used to bring in the first partition. Just `current_switch`
 * without saving the current partition since there is no current partition.
 */
void current_init(part_t *part);
