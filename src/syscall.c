// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "syscall.h"

#include "csr.h"
#include "defs.h"
#include "inst_code.h"
#include "utraps.h"

void ksk_yield(void);
void ksk_send(void);
void ksk_recv(void);
void ksk_pad(void);

typedef void (*handler_t)(void);
static const handler_t handlers[4] = {ksk_yield, ksk_send, ksk_recv, ksk_pad};

void handle_syscall(word_t mcause, word_t mtval) {
    word_t syscall_nr = current->regs.a7;
    word_t pc;
    CSRR(pc, mepc);
    CSRW(mepc, pc + 4);
    handlers[syscall_nr & 0x3]();
}

void ksk_yield(void) { return; }

void ksk_send(void) { return; }

void ksk_recv(void) { return; }

// This is just for padding the handlers array.
void ksk_pad(void) {}
