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
#include "csr.h"
#include "kernel.h"
#include "traps.h"
Process processes[NR_PROCS];// = CONFIG_PROC;
Inbox inboxes[NR_PROCS][NR_PROCS];

void InitCPU(void) { /* Set CPU frequency and so on. */
}

void InitKernel(void) {
  CSRWI(CSR_MSTATUS, 0);
  CSRW(CSR_MTVEC, TrapEntry);
}
