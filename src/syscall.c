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

#include "syscall.h"
#include "user_trap.h"
#include "csr.h"
#include "inst_code.h"
#include "util.h"

typedef pcb_t* (*handler_t)(pcb_t *pcb);

pcb_t* ksk_Nothing(pcb_t *pcb) {
    return pcb;
}

static handler_t syscall_handlers[] = {
    [0] = ksk_Nothing,
    [1] = ksk_Nothing,
    [2] = ksk_Nothing,
    [3] = ksk_Nothing,
};

pcb_t* handle_syscall(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) {
    uintptr_t syscall_number = pcb->gr[GR_T0];
    if (syscall_number < ARRAY_SIZE(syscall_handlers)) {
        return syscall_handlers[syscall_number](pcb);
    } else {
        return handle_user_excpt(pcb, MCAUSE_ILLEGAL_INSTRUCTION, INST_ECALL);
    }
}

