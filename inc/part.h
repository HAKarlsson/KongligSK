// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#pragma once
#include "config.h"
#include "csr.h"
#include "defs.h"

typedef unsigned long long word_t;

// General purpose registers.
typedef struct regs {
    word_t pc;                                        // pc
    word_t ra, sp;                                    // x1-x2
    word_t gp, tp;                                    // x3-x4
    word_t t0, t1, t2;                                // x5-x7
    word_t s0, s1;                                    // x8-x9
    word_t a0, a1;                                    // x10-x11
    word_t a2, a3, a4, a5, a6, a7;                    // x12-x17
    word_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;  // x18-x27
    word_t t3, t4, t5, t6;                            // x28-x31
} regs_t;

// User trap setup and handling registers.
typedef struct ut_regs {
    word_t ustatus, uie, utvec;
    word_t uscratch, uepc, ucause, utval, uip;
} ut_regs_t;

// Physical memory protection registers.
typedef struct pmp {
    word_t cfg0;
    word_t addr0;
    word_t addr1;
    word_t addr2;
    word_t addr3;
    word_t addr4;
    word_t addr5;
    word_t addr6;
    word_t addr7;
} pmp_t;

// Partition control block.
typedef struct part {
    regs_t regs;
    pmp_t pmp;
    ut_regs_t ut_regs;
    word_t id;
} part_t;

extern part_t parts[NR_PARTS];
register part_t* current __asm__("x4");

static inline void save_regs(part_t* part) {
    // clang-format off
    __asm__ volatile (
    "sd     x5,   (5 * %0)(%1);"
    "sd     x6,   (6 * %0)(%1);"
    "sd     x7,   (7 * %0)(%1);"
    "sd     x8,   (8 * %0)(%1);"
    "sd     x9,   (9 * %0)(%1);"
    "sd     x18, (18 * %0)(%1);"
    "sd     x19, (19 * %0)(%1);"
    "sd     x20, (20 * %0)(%1);"
    "sd     x21, (21 * %0)(%1);"
    "sd     x22, (22 * %0)(%1);"
    "sd     x23, (23 * %0)(%1);"
    "sd     x24, (24 * %0)(%1);"
    "sd     x25, (25 * %0)(%1);"
    "sd     x26, (26 * %0)(%1);"
    "sd     x27, (27 * %0)(%1);"
    "sd     x28, (28 * %0)(%1);"
    "sd     x29, (29 * %0)(%1);"
    "sd     x30, (30 * %0)(%1);"
    "sd     x31, (31 * %0)(%1);"
    "csrr   x5, mscratch;"         // load user tp from mscratch
    "csrr   x6, mepc;"             // load user pc from mscratch
    "sd     x5,   (4 * %0)(%1);"   // save user tp to part
    "sd     x6,   (0 * %0)(%1);"   // save user pc to part
    :: "i"(REGBYTES), "r"(&part->regs)
    : "memory");
    // clang-format on
}

// Load registers tp, t0-t6 and s0-s11.
// Other registers are loaded in trap_exit.
static inline void load_regs(const part_t* part) {
    // clang-format off
    __asm__ volatile (
    "ld     x5,   (4 * %0)(%1);"   // load user tp from part 
    "ld     x6,   (0 * %0)(%1);"   // load user pc from part 
    "csrw   mscratch, x5;"         // save user tp to mscratch
    "csrw   mepc, x5;"             // save user pc to mepc 
    "ld     x5,   (5 * %0)(%1);"
    "ld     x6,   (6 * %0)(%1);"
    "ld     x7,   (7 * %0)(%1);"
    "ld     x8,   (8 * %0)(%1);"
    "ld     x9,   (9 * %0)(%1);"
    "ld     x18, (18 * %0)(%1);"
    "ld     x19, (19 * %0)(%1);"
    "ld     x20, (20 * %0)(%1);"
    "ld     x21, (21 * %0)(%1);"
    "ld     x22, (22 * %0)(%1);"
    "ld     x23, (23 * %0)(%1);"
    "ld     x24, (24 * %0)(%1);"
    "ld     x25, (25 * %0)(%1);"
    "ld     x26, (26 * %0)(%1);"
    "ld     x27, (27 * %0)(%1);"
    "ld     x28, (28 * %0)(%1);"
    "ld     x29, (29 * %0)(%1);"
    "ld     x30, (30 * %0)(%1);"
    "ld     x31, (31 * %0)(%1);"
    :: "i"(REGBYTES), "r"(&part->regs));
    // clang-format on
}

static inline void set_pmp(const part_t* part) {
    CSRW(pmpcfg0, part->pmp.cfg0);
    CSRW(pmpaddr0, part->pmp.addr0);
    CSRW(pmpaddr1, part->pmp.addr1);
    CSRW(pmpaddr2, part->pmp.addr2);
    CSRW(pmpaddr3, part->pmp.addr3);
    CSRW(pmpaddr4, part->pmp.addr4);
    CSRW(pmpaddr5, part->pmp.addr5);
    CSRW(pmpaddr6, part->pmp.addr6);
    CSRW(pmpaddr7, part->pmp.addr7);
}
