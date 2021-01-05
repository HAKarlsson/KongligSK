// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "sched.h"

#include "csr.h"

// static inline uint64_t read_mtime(void);
// static inline uint64_t write_mtimecmp(void);

void handle_mtimer(uintptr_t mcause, uintptr_t mtval) {
	current_switch(current);
}
