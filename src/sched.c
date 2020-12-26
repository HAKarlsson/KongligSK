// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#include "sched.h"

#include "csr.h"

// static inline uint64_t read_mtime(void);
// static inline uint64_t write_mtimecmp(void);

void handle_mtimer(word_t mcause, word_t mtval) {
    save_regs(current);
    set_pmp(current);
    load_regs(current);
}
