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
#include "user_trap.h"

pcb_t *handle_user_excpt(pcb_t *pcb, kernel_t *kernel, uintptr_t mcause, uintptr_t mtval) {
  /* Save user pc. */
  pcb->trap_regs[UEPC] = pcb->regs[PC];
  /* Save trap information. */
  pcb->trap_regs[UCAUSE] = mcause;
  pcb->trap_regs[UTVAL] = mtval;
  /* Disable interrupts and set UPIE if UIE */
  pcb->trap_regs[USTATUS] = (pcb->trap_regs[USTATUS] & 1) << 4;
  /* Jump to trap handler. */
  pcb->regs[PC] = pcb->trap_regs[UTVEC] & ~3UL;
  return pcb;
}
