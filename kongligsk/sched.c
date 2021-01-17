// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "sched.h"

#include "csr.h"

void sched_tail(void);
void sched_tail_init(part_t *);
void sched_tail_swap(part_t *);

// static inline uint64_t read_mtime(void);
// static inline uint64_t write_mtimecmp(void);

void sched_init(void) {
	sched_tail_init(current);
}

void sched(void) {
	sched_tail();
}
