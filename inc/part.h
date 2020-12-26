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
#ifdef RV32
    word_t cfg1;
#endif
    word_t addr0, addr1, addr2, addr3, addr4, addr5, addr6, addr7;
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

// Save registers tp, t0-t6 and s0-s11.
// Other registers are saved in trap_entry.
inline void save_regs(part_t* part) {
    // clang-format off
    __asm__(
      SREG " x5,   (5 * %0)(%1);"
      SREG " x6,   (6 * %0)(%1);"
      SREG " x7,   (7 * %0)(%1);"
      SREG " x8,   (8 * %0)(%1);"
      SREG " x9,   (9 * %0)(%1);"
      SREG " x18, (18 * %0)(%1);"
      SREG " x19, (19 * %0)(%1);"
      SREG " x20, (20 * %0)(%1);"
      SREG " x21, (21 * %0)(%1);"
      SREG " x22, (22 * %0)(%1);"
      SREG " x23, (23 * %0)(%1);"
      SREG " x24, (24 * %0)(%1);"
      SREG " x25, (25 * %0)(%1);"
      SREG " x26, (26 * %0)(%1);"
      SREG " x27, (27 * %0)(%1);"
      SREG " x28, (28 * %0)(%1);"
      SREG " x29, (29 * %0)(%1);"
      SREG " x30, (30 * %0)(%1);"
      SREG " x31, (31 * %0)(%1);"
      "csrr  x5, mscratch;"         // load user tp from mscratch
      "csrr  x6, mepc;"             // load user pc from mscratch
      SREG " x5,   (4 * %0)(%1);"   // save user tp to part
      SREG " x6,   (0 * %0)(%1);"   // save user pc to part
      :: "i"(REGBYTES), "r"(&part->regs)
      : "memory");
    // clang-format on
}

// Load registers tp, t0-t6 and s0-s11.
// Other registers are loaded in trap_exit.
inline void load_regs(const part_t* part) {
    // clang-format off
    __asm__(
      LREG " x5,   (4 * %0)(%1);"   // load user tp from part 
      LREG " x6,   (0 * %0)(%1);"   // load user pc from part 
      "csrw  mscratch, x5;"         // save user tp to mscratch
      "csrw  mepc, x5;"             // save user pc to mepc 
      LREG " x5,   (5 * %0)(%1);"
      LREG " x6,   (6 * %0)(%1);"
      LREG " x7,   (7 * %0)(%1);"
      LREG " x8,   (8 * %0)(%1);"
      LREG " x9,   (9 * %0)(%1);"
      LREG " x18, (18 * %0)(%1);"
      LREG " x19, (19 * %0)(%1);"
      LREG " x20, (20 * %0)(%1);"
      LREG " x21, (21 * %0)(%1);"
      LREG " x22, (22 * %0)(%1);"
      LREG " x23, (23 * %0)(%1);"
      LREG " x24, (24 * %0)(%1);"
      LREG " x25, (25 * %0)(%1);"
      LREG " x26, (26 * %0)(%1);"
      LREG " x27, (27 * %0)(%1);"
      LREG " x28, (28 * %0)(%1);"
      LREG " x29, (29 * %0)(%1);"
      LREG " x30, (30 * %0)(%1);"
      LREG " x31, (31 * %0)(%1);"
      :: "i"(REGBYTES), "r"(&part->regs));
    // clang-format on
}

inline void set_pmp(const part_t* part) {
    CSRW(pmpcfg0, part->pmp.cfg0);
#ifdef RV32
    CSRW(pmpcfg1, part->pmp.cfg1);
#endif
    CSRW(pmpaddr0, part->pmp.addr0);
    CSRW(pmpaddr1, part->pmp.addr1);
    CSRW(pmpaddr2, part->pmp.addr2);
    CSRW(pmpaddr3, part->pmp.addr3);
    CSRW(pmpaddr4, part->pmp.addr4);
    CSRW(pmpaddr5, part->pmp.addr5);
    CSRW(pmpaddr6, part->pmp.addr6);
    CSRW(pmpaddr7, part->pmp.addr7);
}
