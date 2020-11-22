/*
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 *
 * KongligSK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KongligSK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include "kernel.h"

/**
 * Handles an exception for the proc, using mcause to determine the
 * exception type. mtval is the auxiliary information for the trap.
 */
proc_t* trap_handler(proc_t* proc, uintptr_t mcause, uintptr_t mtval);

void trap_entry(void) NO_RETURN;
void trap_exit(proc_t* proc) NO_RETURN;

proc_t* handle_mtimer(proc_t* proc, uintptr_t mcause, uintptr_t mtval);
proc_t* handle_syscall(proc_t* proc, uintptr_t mcause, uintptr_t mtval);

/**
 * Delegate an exception to proc.
 * mcause and mtval holds the exception type and auxiliary information.
 */
proc_t* handle_uexcpt(proc_t* proc, uintptr_t mcause, uintptr_t mtval);

/**
 * Delegate an interrupt to proc.
 * mcause holds the interrupt type.
 */
proc_t* handle_uintrp(proc_t* proc, uintptr_t mcause, uintptr_t mtval);
