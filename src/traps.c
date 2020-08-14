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
#include "syscall.h"
#include "util.h"
#include "csr.h"
#include "user_trap.h"

typedef pcb_t* (*handler_t)(pcb_t*, uintptr_t, uintptr_t);

const handler_t exception_handlers[] = {
    [MCAUSE_INSTRUCTION_ADDRESS_MISALIGNED] = handle_user_excpt,
    [MCAUSE_INSTRUCTION_ACCESS_FAULT] = handle_user_excpt,
    [MCAUSE_ILLEGAL_INSTRUCTION] = 0,
    [MCAUSE_BREAKPOINT] = handle_user_excpt,
    [MCAUSE_LOAD_ADDRESS_MISALIGNED] = handle_user_excpt,
    [MCAUSE_LOAD_ACCESS_FAULT] = handle_user_excpt,
    [MCAUSE_STORE_ADDRESS_MISALIGNED] = handle_user_excpt,
    [MCAUSE_STORE_ACCESS_FAULT] = handle_user_excpt,
    [MCAUSE_UMODE_ECALL] = handle_syscall,
    [MCAUSE_SMODE_ECALL] = 0,
    [MCAUSE_MMODE_ECALL] = 0,
    [MCAUSE_INSTRUCTION_PAGE_FAULT] = 0,
    [MCAUSE_LOAD_PAGE_FAULT] = 0,
    [MCAUSE_STORE_PAGE_FAULT] = 0,
};

pcb_t* handle_excpt(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) {
    return exception_handlers[mcause](pcb, mcause, mtval);
}

pcb_t* handle_intrp(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) {
    return pcb;
}
