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
#include "inst_code.h"
#include "kernel.h"

typedef struct inbox {
    uintptr_t full;
    uintptr_t msgs[2];
} inbox_t;

inbox_t inboxes[NR_PROCS][NR_PROCS];

typedef proc_t* (*handler_t)(proc_t*);
proc_t* ksk_yield(proc_t* proc);
proc_t* ksk_send(proc_t* proc);
proc_t* ksk_recv(proc_t* proc);

static const handler_t syscall_handlers[] = {
    [0] = ksk_yield,
    [1] = ksk_send,
    [2] = ksk_recv,
};

proc_t* handle_syscall(proc_t* proc, uintptr_t mcause, uintptr_t mtval)
{
    uintptr_t syscall_nr = proc->regs.t0;
    if (syscall_nr < ARRAY_SIZE(syscall_handlers)) {
        proc->regs.pc += 4;
        return syscall_handlers[syscall_nr](proc);
    }
    return handle_uexcpt(proc, MCAUSE_EXCPT_ILLEGAL_INSTRUCTION,
        INST_ECALL);
}

proc_t* ksk_yield(proc_t* proc)
{
    uintptr_t target = proc->regs.a0;
    /* If the target process is invalid, just return the current process. */
    if (target >= NR_PROCS) {
        proc->regs.a0 = 0;
        return proc;
    }
    /* Return the target process. */
    proc->regs.a0 = 1;
    return &procs[target];
}

proc_t* ksk_send(proc_t* proc)
{
    uintptr_t sender = proc->id;
    uintptr_t receiver = proc->regs.a0;
    inbox_t* inbox = &inboxes[receiver][sender];
    /* We must check receiver first, otherwise the inbox check is invalid! */
    if (receiver >= NR_PROCS || inbox->full) {
        // maybe do exception for bad receiver??
        proc->regs.a0 = -1;
        return proc;
    }
    /* Copy the message from regs.ster to inbox, then mark inbox as full. */
    inbox->msgs[0] = proc->regs.a2;
    inbox->msgs[1] = proc->regs.a3;
    inbox->full = 1;
    return proc;
}

proc_t* ksk_recv(proc_t* proc)
{
    uintptr_t sender = proc->regs.a0;
    uintptr_t receiver = proc->id;
    inbox_t* inbox = &inboxes[receiver][sender];
    /* We must check sender first, otherwise the inbox check is invalid! */
    if (sender >= NR_PROCS || !inbox->full) {
        // maybe do exception for bad sender??
        proc->regs.a0 = -1;
        return proc;
    }
    /* Copy the message from inbox to regs.ster, then mark inbox as empty. */
    proc->regs.a2 = inbox->msgs[0];
    proc->regs.a3 = inbox->msgs[1];
    inbox->full = 0;
    return proc;
}
