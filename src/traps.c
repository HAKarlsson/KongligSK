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
#include "traps.h"

#include "csr.h"
#include "machine_timer.h"
#include "syscall.h"
#include "user_trap.h"
#include "util.h"

typedef Process* (*Handler)(Process* pcb, uintptr_t mcause, uintptr_t mtval);

static const Handler handlers[] = {
    /* Execeptions */
    [MCAUSE_EXCPT_INSTRUCTION_ADDRESS_MISALIGNED] = HandleUserException,
    [MCAUSE_EXCPT_INSTRUCTION_ACCESS_FAULT] = HandleUserException,
    [MCAUSE_EXCPT_ILLEGAL_INSTRUCTION] = 0,
    [MCAUSE_EXCPT_BREAKPOINT] = HandleUserException,
    [MCAUSE_EXCPT_LOAD_ADDRESS_MISALIGNED] = HandleUserException,
    [MCAUSE_EXCPT_LOAD_ACCESS_FAULT] = HandleUserException,
    [MCAUSE_EXCPT_STORE_ADDRESS_MISALIGNED] = HandleUserException,
    [MCAUSE_EXCPT_STORE_ACCESS_FAULT] = HandleUserException,
    [MCAUSE_EXCPT_USER_ECALL] = HandleSyscall,
    [MCAUSE_EXCPT_SUPERVISOR_ECALL] = 0,
    [MCAUSE_EXCPT_MACHINE_ECALL] = 0,
    [MCAUSE_EXCPT_INSTRUCTION_PAGE_FAULT] = 0,
    [MCAUSE_EXCPT_LOAD_PAGE_FAULT] = 0,
    [MCAUSE_EXCPT_STORE_PAGE_FAULT] = 0,
    /* Interrupts */
    [MCAUSE_INTRP_MACHINE_SOFTWARE | 0x10] = 0,
    [MCAUSE_INTRP_MACHINE_TIMER | 0x10] = HandleMachineTimer,
    [MCAUSE_INTRP_MACHINE_EXTERN | 0x10] = 0,
};

Process* TrapHandler(Process* pcb, uintptr_t mcause, uintptr_t mtval)
{
    // If mcause is interrupt, this should be 0x10 (16), otherwise 0.
    uintptr_t intrp_bit = (mcause >> 63) << 4;
    return handlers[mcause | intrp_bit](pcb, mcause, mtval);
}
