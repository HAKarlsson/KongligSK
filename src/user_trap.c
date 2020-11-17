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

Process* HandleUserException(Process* proc, uintptr_t mcause, uintptr_t mtval)
{
    /* Save user pc. */
    proc->ut_regs.uepc = proc->regs.pc;
    /* Save trap information. */
    proc->ut_regs.ucause = mcause;
    proc->ut_regs.utval = mtval;
    /* Disable interrupts and set UPIE if UIE */
    proc->ut_regs.ustatus = (proc->ut_regs.ustatus & 1) << 4;
    /* User jumps to trap handler. */
    proc->regs.pc = proc->ut_regs.utvec & ~3UL;
    return proc;
}
