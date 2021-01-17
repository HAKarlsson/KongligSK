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
void trap_handler(void);

/*
 * Entry function for traps.
 *
 * On partition exception/interrupt, the system will jump to this function.
 * Saves the partition register ra, sp, gp, tp, a0-a7 to `current` (other
 * registers are not touch by the kernel except on partition swap), then calls
 * trap_handler for the actual handling of the trap. Once the trap handler has
 * finished, goes to trap_exit
 */
void trap_entry(void);

/**
 * Delegate a trap to partition.
 */
void handle_utrap(void);

/**
 * Delegate a trap to partition.
 */
void handle_mtimer(void);
