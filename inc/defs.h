// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#pragma once

#if __riscv_xlen == 32
#define RV32
#define SEL(x, y) x
#else
#define RV64
#define SEL(x, y) y
#endif

#ifdef __ASSEMBLER__
#define SREG SEL(sw, sd)
#define LREG SEL(lw, ld)
#else
#define SREG SEL("sw", "sd")
#define LREG SEL("lw", "ld")
#endif

#define REGBYTES SEL(4, 8)
#define REGBITS SEL(32, 64)

#define NO_RETURN __attribute__((noreturn))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define INST_ECALL 0x00000073
#define INST_URET 0x00200073
