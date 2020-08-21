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

#include "kernel.h"
#include "pmp.h"
#include "syscall.h"
#include "inst_code.h"
#include "csr.h"
#include "user_trap.h"
#include "util.h"

typedef pcb_t *(*handler_t)(pcb_t *pcb, kernel_t *kernel);

/* Placeholder. */
pcb_t *ksk_Nothing(pcb_t *pcb, kernel_t *kernel) { return pcb; }

pcb_t *ksk_YieldTo(pcb_t *pcb, kernel_t *kernel) {
    uintptr_t target = pcb->regs[A0];
    /* If the target process is invalid, just return the current process. */
    if (target >= PCB_NUM)
        return pcb;
    /* Return the target process. */
    return load_pmp(&kernel->processes[target]);
}

pcb_t *ksk_Send(pcb_t *pcb, kernel_t *kernel) {
    uintptr_t sender = pcb->id;
    uintptr_t receiver = pcb->regs[A0];
    inbox_t *inbox = &kernel->inboxes[receiver][sender];
    /* We must check receiver first, otherwise the inbox check is invalid! */
    if (receiver >= PCB_NUM || inbox->full)
        return pcb;
    /* Copy the message from register to inbox, then mark inbox as full. */
    for (int i = 0; i < MSGS_LEN; ++i)
        inbox->msgs[i] = pcb->regs[A2 + i];
    inbox->full = 1;
    return pcb;
}

pcb_t *ksk_Recv(pcb_t *pcb, kernel_t *kernel) {
    uintptr_t sender = pcb->regs[A0];
    uintptr_t receiver = pcb->id;
    inbox_t *inbox = &kernel->inboxes[receiver][sender];
    /* We must check sender first, otherwise the inbox check is invalid! */
    if (sender >= PCB_NUM || !inbox->full)
        return pcb;
    /* Copy the message from inbox to register, then mark inbox as empty. */
    for (int i = 0; i < MSGS_LEN; ++i)
        pcb->regs[A2 + i] = inbox->msgs[i];
    inbox->full = 0;
    return pcb;
}

static handler_t syscall_handlers[] = {
    [0] = ksk_YieldTo,
    [1] = ksk_Send,
    [2] = ksk_Recv,
    [3] = ksk_Nothing,
};

pcb_t *handle_syscall(pcb_t *pcb, kernel_t *kernel, uintptr_t mcause, uintptr_t mtval) {
  uintptr_t syscall_number = pcb->regs[T0];
  pcb->regs[PC] += 4;
  if (syscall_number < ARRAY_SIZE(syscall_handlers))
    return syscall_handlers[syscall_number](pcb, kernel);
  pcb->regs[PC] -= 4;
  return handle_user_excpt(pcb, kernel, MCAUSE_ILLEGAL_INSTRUCTION, INST_ECALL);
}
