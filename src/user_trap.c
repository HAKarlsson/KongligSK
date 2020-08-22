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

Process *HandleUserException(Process *proc, Kernel *kernel, uintptr_t mcause,
                             uintptr_t mtval) {
  /* Save user pc. */
  proc->trap_regs[UEPC] = proc->regs[PC];
  /* Save trap information. */
  proc->trap_regs[UCAUSE] = mcause;
  proc->trap_regs[UTVAL] = mtval;
  /* Disable interrupts and set UPIE if UIE */
  proc->trap_regs[USTATUS] = (proc->trap_regs[USTATUS] & 1) << 4;
  /* User jumps to trap handler. */
  proc->regs[PC] = proc->trap_regs[UTVEC] & ~3UL;
  return proc;
}
