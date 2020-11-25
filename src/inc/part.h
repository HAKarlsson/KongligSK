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
#pragma once

#include "config.h"
#include "csr.h"
#include "util.h"

typedef unsigned long word_t;
typedef unsigned long long uint64_t;

/* General purpose registers */
typedef struct regs {
    word_t pc;
    word_t ra;
    word_t sp;
    word_t gp;
    word_t tp;
    word_t t0;
    word_t t1;
    word_t t2;
    word_t s0;
    word_t s1;
    word_t a0;
    word_t a1;
    word_t a2;
    word_t a3;
    word_t a4;
    word_t a5;
    word_t a6;
    word_t a7;
    word_t s2;
    word_t s3;
    word_t s4;
    word_t s5;
    word_t s6;
    word_t s7;
    word_t s8;
    word_t s9;
    word_t s10;
    word_t s11;
    word_t t3;
    word_t t4;
    word_t t5;
    word_t t6;
} regs_t;

/* User trap setup and handling registers */
typedef struct ut_regs {
    word_t ustatus;
    word_t uie;
    word_t utvec;
    word_t uscratch;
    word_t uepc;
    word_t ucause;
    word_t utval;
    word_t uip;
} ut_regs_t;

/* Physical memory protection registers */
typedef struct pmp {
    union {
#ifdef RV32
        struct {
            word_t cfg0;
            word_t cfg1;
        };
#else
        word_t cfg0
#endif
        uint64_t cfg;
    };
    word_t addr0;
    word_t addr1;
    word_t addr2;
    word_t addr3;
    word_t addr4;
    word_t addr5;
    word_t addr6;
    word_t addr7;
} pmp_t;

/* Partition control block */
typedef struct part {
    regs_t regs;
    pmp_t pmp;
    ut_regs_t ut_regs;
    /* Partition id */
    word_t id;
} part_t;
extern part_t parts[NR_PARTS];

#ifdef RV32
#define SAVEX(n)                                                              \
    __asm__("sw x" #n ", (" #n " * 4)(%0);" ::"r"(&part->regs) : "memory")
#else
#define SAVEX(n)                                                              \
    __asm__("sd x" #n ", (" #n " * 8)(%0);" ::"r"(&part->regs) : "memory")
#endif
// Save registers tp, t0-t6 and s0-s11.
// Other registers are saved in trap_entry.
inline void save_regs(part_t* part)
{
    SAVEX(4);
    SAVEX(5);
    SAVEX(6);
    SAVEX(7);
    SAVEX(8);
    SAVEX(9);
    SAVEX(18);
    SAVEX(19);
    SAVEX(20);
    SAVEX(21);
    SAVEX(22);
    SAVEX(23);
    SAVEX(24);
    SAVEX(25);
    SAVEX(26);
    SAVEX(27);
    SAVEX(28);
    SAVEX(29);
    SAVEX(30);
    SAVEX(31);
}

#ifdef RV32
#define LOADX(n) __asm__("lw x" #n ", (" #n " * 4)(%0);" ::"r"(&part->regs))
#else
#define LOADX(n) __asm__("ld x" #n ", (" #n " * 8)(%0);" ::"r"(&part->regs))
#endif
// Load registers tp, t0-t6 and s0-s11.
// Other registers are loaded in trap_exit.
inline void load_regs(const part_t* part)
{
    LOADX(4);
    LOADX(5);
    LOADX(6);
    LOADX(7);
    LOADX(8);
    LOADX(9);
    LOADX(18);
    LOADX(19);
    LOADX(20);
    LOADX(21);
    LOADX(22);
    LOADX(23);
    LOADX(24);
    LOADX(25);
    LOADX(26);
    LOADX(27);
    LOADX(28);
    LOADX(29);
    LOADX(30);
    LOADX(31);
}

inline void set_pmp(const part_t* part)
{
    CSRW(CSR_PMPCFG0, part->pmp.cfg0);
#ifdef RV32
    CSRW(CSR_PMPCFG1, part->pmp.cfg1);
#endif
    CSRW(CSR_PMPADDR0, part->pmp.addr0);
    CSRW(CSR_PMPADDR1, part->pmp.addr1);
    CSRW(CSR_PMPADDR2, part->pmp.addr2);
    CSRW(CSR_PMPADDR3, part->pmp.addr3);
    CSRW(CSR_PMPADDR4, part->pmp.addr4);
    CSRW(CSR_PMPADDR5, part->pmp.addr5);
    CSRW(CSR_PMPADDR6, part->pmp.addr6);
    CSRW(CSR_PMPADDR7, part->pmp.addr7);
}
