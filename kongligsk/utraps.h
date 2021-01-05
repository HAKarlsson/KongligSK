// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#pragma once
#include "part.h"

/**
 * Delegate a trap to partition.
 * mcause and mtval holds the trap type and auxiliary information.
 */
void handle_utrap(uintptr_t mcause, uintptr_t mtval);
