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

typedef Process *(*ExcptHandler)(Process *pcb, uintptr_t mcause,
                                 uintptr_t mtval);
typedef Process *(*IntrpHandler)(Process *pcb, uintptr_t mcause);

static const ExcptHandler excpt_handlers[] = {
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
};

static const IntrpHandler intrp_handlers[] = {
    [MCAUSE_INTRP_MACHINE_SOFTWARE] = 0,
    [MCAUSE_INTRP_MACHINE_TIMER] = HandleMachineTimer,
    [MCAUSE_INTRP_MACHINE_EXTERN] = 0,
};

Process *TrapHandler(Process *pcb, uintptr_t mcause, uintptr_t mtval) {
  if ((intptr_t)mcause < 0)
    return intrp_handlers[0xFFF & mcause](pcb, mcause);
  return excpt_handlers[mcause](pcb, mcause, mtval);
}
