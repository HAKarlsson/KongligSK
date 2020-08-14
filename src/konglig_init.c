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
#include "traps.h"
#include "kernel.h"

void cpu_init(void) {
    /* Set CPU frequency and so on. */
}

void kernel_init(void) {
    csrw(CSR_MSTATUS, 0); 
    pcb_t pcb = kernel.processes[0];
    csrw(CSR_PMPCFG0, pcb.pmpcfg[0]);
    csrw(CSR_PMPADDR0, pcb.pmpaddr[0]);
    /* We should write to MTVEC last. This causes initialization 
     * exception to be caught in head.S. */
    csrw(CSR_MTVEC, (uintptr_t)trap_entry);
    trap_exit(&pcb);
}