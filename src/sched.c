/*
 * This file is part of KongligSK.
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
#include "sched.h"

#include "csr.h"

// static inline uint64_t read_mtime(void);
// static inline uint64_t write_mtimecmp(void);

void handle_mtimer(word_t mcause, word_t mtval)
{
    save_regs(curr_part);
    set_pmp(curr_part);
    load_regs(curr_part);
}