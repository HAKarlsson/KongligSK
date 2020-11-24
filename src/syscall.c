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
#include "util.h"
#include "inst_code.h"
#include "utraps.h"

#define NR_MSGS 4
typedef struct inbox {
    uintptr_t full;
    uintptr_t msgs[NR_MSGS];
} inbox_t;
static inbox_t inboxes[NR_PARTS][NR_PARTS];

static part_t* ksk_yield(part_t* part) __attribute((noinline));
static part_t* ksk_send(part_t* part) __attribute((noinline));
static part_t* ksk_recv(part_t* part) __attribute((noinline));

typedef part_t* (*handler_t)(part_t* part);
static const handler_t handlers[] = { ksk_yield, ksk_send, ksk_recv };

part_t* handle_syscall(part_t* part, uintptr_t mcause, uintptr_t mtval)
{
    uintptr_t syscall_nr = part->regs.a7;
    if (syscall_nr < ARRAY_SIZE(handlers))
        return handlers[syscall_nr](part);
    return handle_uexcpt(part, MCAUSE_EXCPT_ILLEGAL_INSTRUCTION, INST_ECALL);
}

part_t* ksk_yield(part_t* part)
{
    part->regs.pc += 4;
    uintptr_t target = part->regs.a0;
    /* If the target partess is invalid, just return the current partess. */
    if (target >= NR_PARTS) {
        part->regs.a0 = 0;
        return part;
    }
    /* Return the target partess. */
    part->regs.a0 = 1;
    return &parts[target];
}

part_t* ksk_send(part_t* part)
{
    part->regs.pc += 4;
    uintptr_t sender = part->id;
    uintptr_t receiver = part->regs.a0;
    inbox_t* inbox = &inboxes[receiver][sender];
    /* We must check receiver first, otherwise the inbox check is invalid! */
    if (receiver >= NR_PARTS || inbox->full) {
        // maybe do exception for bad receiver??
        part->regs.a0 = -1;
        return part;
    }
    /* Copy the message from regs.ster to inbox, then mark inbox as full. */
    uintptr_t* msgs = &(part->regs.a2);
    for (int i = 0; i < NR_MSGS; ++i)
        inbox->msgs[i] = msgs[i];
    inbox->full = 1;
    return part;
}

part_t* ksk_recv(part_t* part)
{
    part->regs.pc += 4;
    uintptr_t sender = part->regs.a0;
    uintptr_t receiver = part->id;
    inbox_t* inbox = &inboxes[receiver][sender];
    /* We must check sender first, otherwise the inbox check is invalid! */
    if (sender >= NR_PARTS || !inbox->full) {
        // maybe do exception for bad sender??
        part->regs.a0 = -1;
        return part;
    }
    /* Copy the message from inbox to register, then mark inbox as empty. */
    uintptr_t* msgs = &(part->regs.a2);
    for (int i = 0; i < NR_MSGS; ++i)
        msgs[i] = inbox->msgs[i];
    inbox->full = 0;
    return part;
}
