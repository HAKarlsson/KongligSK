// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "syscall.h"

#include "csr.h"
#include "defs.h"

static void ksk_yield(void);
static void ksk_send(void);
static void ksk_recv(void);
static void ksk_pad(void);

typedef void (*handler_t)(void);
static const handler_t handlers[4] = {ksk_yield, ksk_send, ksk_recv, ksk_pad};

void handle_syscall(void) {
	register uintptr_t syscall_nr asm("t0");
	write_csr(mepc, read_csr(mepc) + 4);
	handlers[syscall_nr & 0x3]();
}

static void ksk_yield(void) {}

static void ksk_send(void) {}

static void ksk_recv(void) {}

// This is just for padding the handlers array.
static void ksk_pad(void) {}
