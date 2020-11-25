/* * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 *
 * KongligSK is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * KongligSK is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with KongligSK.  If not, see
 * <https://www.gnu.org/licenses/>.
 */
#include "syscall.h"

#include "csr.h"
#include "inst_code.h"
#include "util.h"
#include "utraps.h"

#define NR_MSGS 4
typedef struct inbox {
    word_t full;
    word_t msgs[NR_MSGS];
} inbox_t;
static inbox_t inboxes[NR_PARTS][NR_PARTS];

static part_t* ksk_yield(part_t* part);
static part_t* ksk_send(part_t* part);
static part_t* ksk_recv(part_t* part);
static part_t* ksk_wait_send(part_t* part);
static part_t* ksk_wait_recv(part_t* part);

typedef part_t* (*handler_t)(part_t* part);
static const handler_t handlers[]
    = { ksk_yield, ksk_send, ksk_recv, ksk_wait_send, ksk_wait_recv };

part_t* handle_syscall(part_t* part, word_t mcause, word_t mtval)
{
    word_t syscall_nr = part->regs.a7;
    if (syscall_nr < ARRAY_SIZE(handlers)) {
        part->regs.pc += 4;
        return handlers[syscall_nr](part);
    }
    return handle_uexcpt(part, MCAUSE_EXCPT_USER_ECALL, 0);
}

part_t* ksk_yield(part_t* part)
{
    word_t target = part->regs.a0;
    /* If the target partition is invalid, return the
     * current partition. */
    if (target >= NR_PARTS)
        return handle_uexcpt(part, MCAUSE_EXCPT_USER_ECALL, 0);
    /* Return the target partition. */
    return part;
}

part_t* ksk_send(part_t* part)
{
    word_t sender = part->id;
    word_t receiver = part->regs.a0;
    inbox_t* inbox = &inboxes[receiver][sender];
    /* We must check receiver first, otherwise the inbox
     * check is invalid! */
    if (receiver >= NR_PARTS || inbox->full) {
        // maybe do exception for bad receiver??
        part->regs.a0 = 0;
        return part;
    }
    /* Copy the message from register to inbox, then mark
     * inbox as full. */
    word_t* msgs = &(part->regs.a2);
    inbox->msgs[0] = msgs[0];
    inbox->msgs[1] = msgs[1];
    inbox->msgs[2] = msgs[2];
    inbox->msgs[3] = msgs[3];
    inbox->full = 1;
    part->regs.a0 = 1;
    return part;
}

part_t* ksk_recv(part_t* part)
{
    word_t sender = part->regs.a0;
    word_t receiver = part->id;
    inbox_t* inbox = &inboxes[receiver][sender];
    /* We must check sender first, otherwise the inbox check
     * is invalid! */
    if (sender >= NR_PARTS || !inbox->full) {
        // maybe do exception for bad sender??
        part->regs.a0 = 0;
        return part;
    }
    /* Copy the message from inbox to register, then mark
     * inbox as empty. */
    word_t* msgs = &(part->regs.a2);
    msgs[0] = inbox->msgs[0];
    msgs[1] = inbox->msgs[1];
    msgs[2] = inbox->msgs[2];
    msgs[3] = inbox->msgs[3];
    inbox->full = 0;
    part->regs.a0 = 1;
    return part;
}

part_t* ksk_wait_send(part_t* part) { return part; }

part_t* ksk_wait_recv(part_t* part) { return part; }
