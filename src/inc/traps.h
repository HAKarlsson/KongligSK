/*
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 *
 * KongligSK is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * KongligSK is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with KongligSK.  If not, see
 * <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "part.h"
#include "util.h"

// Handles an exception for the partition, using mcause to
// determine the exception type. mtval is the auxiliary
// information for the trap.
part_t* trap_handler(part_t* part, word_t mcause, word_t mtval);

void trap_entry(void) NO_RETURN;
void trap_exit(part_t* part) NO_RETURN;
