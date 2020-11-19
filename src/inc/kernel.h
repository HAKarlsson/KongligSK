/*
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 *
 * KongligSK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KongligSK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef KSK_KERNEL_H
#define KSK_KERNEL_H

#include "config.h"
#include "util.h"

typedef unsigned long uintptr_t;

typedef struct inbox {
    uintptr_t full;
    uintptr_t msgs[2];
} Inbox;

/* General purpose registers */
typedef struct regs {
    uintptr_t pc;
    uintptr_t ra;
    uintptr_t sp;
    uintptr_t gp;
    uintptr_t tp;
    uintptr_t t0;
    uintptr_t t1;
    uintptr_t t2;
    uintptr_t s0;
    uintptr_t s1;
    uintptr_t a0;
    uintptr_t a1;
    uintptr_t a2;
    uintptr_t a3;
    uintptr_t a4;
    uintptr_t a5;
    uintptr_t a6;
    uintptr_t a7;
    uintptr_t s2;
    uintptr_t s3;
    uintptr_t s4;
    uintptr_t s5;
    uintptr_t s6;
    uintptr_t s7;
    uintptr_t s8;
    uintptr_t s9;
    uintptr_t s10;
    uintptr_t s11;
    uintptr_t t3;
    uintptr_t t4;
    uintptr_t t5;
    uintptr_t t6;
} regs_t;

/* User trap setup and handling registers */
typedef struct ut_regs {
    uintptr_t ustatus;
    uintptr_t uie;
    uintptr_t utvec;
    uintptr_t uscratch;
    uintptr_t uepc;
    uintptr_t ucause;
    uintptr_t utval;
    uintptr_t uip;
} ut_regs_t;

/* Physical memory protection registers */
typedef struct pmp {
    uintptr_t cfg0;
    uintptr_t addr0;
    uintptr_t addr1;
    uintptr_t addr2;
    uintptr_t addr3;
    uintptr_t addr4;
    uintptr_t addr5;
    uintptr_t addr6;
    uintptr_t addr7;
} pmp_t;

/* Process control block */
typedef struct process {
    regs_t regs;
    pmp_t pmp;
    ut_regs_t ut_regs;
    /* Process id */
    uintptr_t id;
} Process;

void InitCPU(void);
void InitKernel(void);
extern Process processes[NR_PROCS];
extern Inbox inboxes[NR_PROCS][NR_PROCS];

#endif /* KSK_KERNEL_H */
