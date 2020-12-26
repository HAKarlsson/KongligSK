// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#pragma once
#include "part.h"

/**
 * Delegate a trap to partition.
 * mcause and mtval holds the trap type and auxiliary information.
 */
void handle_utrap(word_t mcause, word_t mtval);
