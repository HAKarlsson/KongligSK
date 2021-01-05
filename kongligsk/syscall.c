// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "syscall.h"

#include "csr.h"
#include "defs.h"
#include "utraps.h"

void ksk_yield(void);
void ksk_send(void);
void ksk_recv(void);
void ksk_pad(void);

typedef void (*handler_t)(void);
static const handler_t handlers[4] = {ksk_yield, ksk_send, ksk_recv, ksk_pad};

void handle_syscall(uintptr_t mcause, uintptr_t mtval) {
	register uintptr_t syscall_nr asm("t0");
	write_csr(mepc, read_csr(mepc) + 4);
	handlers[syscall_nr & 0x3]();
}

void ksk_yield(void) {}

void ksk_send(void) {}

void ksk_recv(void) {}

// This is just for padding the handlers array.
void ksk_pad(void) {}
