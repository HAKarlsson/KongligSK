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

part_t* handle_uexcpt(part_t* part, word_t mcause, word_t mtval)
{
    /* Save user pc. */
    part->ut_regs.uepc = part->regs.pc;
    /* Save trap information. */
    part->ut_regs.ucause = mcause;
    part->ut_regs.utval = mtval;
    /* Disable interrupts and set UPIE if UIE */
    part->ut_regs.ustatus = (part->ut_regs.ustatus & 1) << 4;
    /* User jumps to trap handler. */
    part->regs.pc = part->ut_regs.utvec & ~3UL;
    return part;
}

part_t* handle_uintrp(part_t* part, word_t mcause, word_t mtval)
{
    /* Save user pc. */
    part->ut_regs.uepc = part->regs.pc;
    /* Save trap information. */
    part->ut_regs.ucause = mcause;
    part->ut_regs.utval = mtval;
    /* Disable interrupts and set UPIE if UIE */
    part->ut_regs.ustatus = (part->ut_regs.ustatus & 1) << 4;
    /* User jumps to trap handler. */
    part->regs.pc = part->ut_regs.utvec & ~3UL;
    /* Add offset if vectored mode. */
    if (part->ut_regs.utvec & 1)
        part->regs.pc += (mcause << 2);
    return part;
}
