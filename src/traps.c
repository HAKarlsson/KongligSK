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
#include "sched.h"
#include "syscall.h"
#include "util.h"
#include "utraps.h"

typedef part_t* (*handler_t)(part_t* pcb, uintptr_t mcause, uintptr_t mtval);

static const handler_t handlers[] = {
    /* Execeptions */
    [MCAUSE_EXCPT_INSTRUCTION_ADDRESS_MISALIGNED] = handle_uexcpt,
    [MCAUSE_EXCPT_INSTRUCTION_ACCESS_FAULT] = handle_uexcpt,
    [MCAUSE_EXCPT_ILLEGAL_INSTRUCTION] = 0,
    [MCAUSE_EXCPT_BREAKPOINT] = handle_uexcpt,
    [MCAUSE_EXCPT_LOAD_ADDRESS_MISALIGNED] = handle_uexcpt,
    [MCAUSE_EXCPT_LOAD_ACCESS_FAULT] = handle_uexcpt,
    [MCAUSE_EXCPT_STORE_ADDRESS_MISALIGNED] = handle_uexcpt,
    [MCAUSE_EXCPT_STORE_ACCESS_FAULT] = handle_uexcpt,
    [MCAUSE_EXCPT_USER_ECALL] = handle_syscall,
    [MCAUSE_EXCPT_SUPERVISOR_ECALL] = 0,
    [MCAUSE_EXCPT_MACHINE_ECALL] = 0,
    [MCAUSE_EXCPT_INSTRUCTION_PAGE_FAULT] = 0,
    [MCAUSE_EXCPT_LOAD_PAGE_FAULT] = 0,
    [MCAUSE_EXCPT_STORE_PAGE_FAULT] = 0,
    /* Interrupts */
    [MCAUSE_INTRP_MACHINE_SOFTWARE | 0x10] = 0,
    [MCAUSE_INTRP_MACHINE_TIMER | 0x10] = handle_mtimer,
    [MCAUSE_INTRP_MACHINE_EXTERN | 0x10] = handle_uintrp,
};

part_t* trap_handler(part_t* pcb, uintptr_t mcause, uintptr_t mtval)
{
    // If mcause is interrupt, this should be 0x10 (16), otherwise 0.
    uintptr_t intrp_bit = (mcause >> (REGBITS - 1)) << 4;
    return handlers[mcause | intrp_bit](pcb, mcause, mtval);
}
