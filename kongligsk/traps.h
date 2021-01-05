// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#pragma once
#include "defs.h"
#include "part.h"

/*
 * Handle partition trap.
 *
 * Simple uses mcause to find the specific interrupt/exception handler.
 */
void trap_handler(uintptr_t mcause, uintptr_t mtval);

/*
 * Entry function for traps.
 *
 * On partition exception/interrupt, the system will jump to this function.
 * Saves the partition register ra, sp, gp, tp, a0-a7 to `current` (other
 * registers are not touch by the kernel except on partition swap), then calls
 * trap_handler for the actual handling of the trap. Once the trap handler has
 * finished, goes to trap_exit
 */
void trap_entry(void) NO_RETURN;

/*
 * Exit function for traps.
 *
 * Brings partition `current`'s registers ra, sp, gp, tp, a0-a7  to context
 * (other registers are already in context), then calls mret.
 */
void trap_exit(void) NO_RETURN;
