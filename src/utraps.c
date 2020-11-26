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
#include "utraps.h"

void handle_utrap(word_t mcause, word_t mtval)
{
    /* Save trap information. */
    CURRENT.ut_regs.ucause = mcause;
    CURRENT.ut_regs.utval = mtval;
    /* Disable interrupts and set UPIE if UIE */
    CURRENT.ut_regs.ustatus = (CURRENT.ut_regs.ustatus & 1) << 4;
    /* User jumps to trap handler. */
    CURRENT.ut_regs.uepc = CURRENT.regs.pc;
    word_t trap_pc = CURRENT.ut_regs.utvec & ~3UL;
    if (CURRENT.ut_regs.utvec & 1 && (long)mcause < 0)
        trap_pc += (mcause << 2); // if vectored mode, add offset
    CSRRW(CURRENT.ut_regs.uepc, CSR_MEPC, trap_pc);
}
