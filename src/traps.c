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
#include "syscall.h"
#include "user_trap.h"
#include "util.h"

typedef Process *(*Handler)(Process *, Kernel *, uintptr_t, uintptr_t);

static const Handler exception_handlers[] = {
    [MCAUSE_INSTRUCTION_ADDRESS_MISALIGNED] = HandleUserException,
    [MCAUSE_INSTRUCTION_ACCESS_FAULT] = HandleUserException,
    [MCAUSE_ILLEGAL_INSTRUCTION] = 0,
    [MCAUSE_BREAKPOINT] = HandleUserException,
    [MCAUSE_LOAD_ADDRESS_MISALIGNED] = HandleUserException,
    [MCAUSE_LOAD_ACCESS_FAULT] = HandleUserException,
    [MCAUSE_STORE_ADDRESS_MISALIGNED] = HandleUserException,
    [MCAUSE_STORE_ACCESS_FAULT] = HandleUserException,
    [MCAUSE_UMODE_ECALL] = HandleSyscall,
    [MCAUSE_SMODE_ECALL] = 0,
    [MCAUSE_MMODE_ECALL] = 0,
    [MCAUSE_INSTRUCTION_PAGE_FAULT] = 0,
    [MCAUSE_LOAD_PAGE_FAULT] = 0,
    [MCAUSE_STORE_PAGE_FAULT] = 0,
};

Process *HandleException(Process *pcb, Kernel *kernel, uintptr_t mcause,
                         uintptr_t mtval) {
  return exception_handlers[mcause](pcb, kernel, mcause, mtval);
}

Process *HandleInterrupt(Process *pcb, Kernel *kernel, uintptr_t mcause,
                         uintptr_t mtval) {
  return pcb;
}
