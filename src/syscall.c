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

#include "csr.h"
#include "inst_code.h"
#include "kernel.h"
#include "user_trap.h"
#include "util.h"

typedef Process* (*Handler)(Process*);

Process* ksk_YieldTo(Process* proc)
{
    uintptr_t target = proc->regs.a0;
    /* If the target process is invalid, just return the current process. */
    if (target >= NR_PROCS) {
        proc->regs.a0 = 0;
        return proc;
    }
    /* Return the target process. */
    proc->regs.a0 = 1;
    return &processes[target];
}

Process* ksk_Send(Process* proc)
{
    uintptr_t sender = proc->id;
    uintptr_t receiver = proc->regs.a0;
    Inbox* inbox = &inboxes[receiver][sender];
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

Process* ksk_Recv(Process* proc)
{
    uintptr_t sender = proc->regs.a0;
    uintptr_t receiver = proc->id;
    Inbox* inbox = &inboxes[receiver][sender];
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

static const Handler syscall_handlers[] = {
    [0] = ksk_YieldTo,
    [1] = ksk_Send,
    [2] = ksk_Recv,
};

Process* HandleSyscall(Process* proc, uintptr_t mcause, uintptr_t mtval)
{
    uintptr_t syscall_number = proc->regs.t0;
    if (syscall_number < ARRAY_SIZE(syscall_handlers)) {
        proc->regs.pc += 4;
        return syscall_handlers[syscall_number](proc);
    }
    return HandleUserException(proc, MCAUSE_EXCPT_ILLEGAL_INSTRUCTION,
        INST_ECALL);
}
