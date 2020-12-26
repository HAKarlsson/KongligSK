// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#pragma once
#include "defs.h"
#include "part.h"

/**
 * Handles an exception for the partition, using mcause to determine the
 * exception type. mtval is the auxiliary information for the trap.
 */
void trap_handler(word_t mcause, word_t mtval);

void trap_entry(void) NO_RETURN;
void trap_exit(void) NO_RETURN;
