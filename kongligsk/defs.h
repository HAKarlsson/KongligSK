// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#pragma once

#include "config.h"

#if __riscv_xlen == 32
#define RV32
#define SEL(x, y) x
#else
#define RV64
#define SEL(x, y) y
#endif

// SEL(x, y) is x for RV32 and y for RV64
#define REGBYTES SEL(4, 8)
#define REGBITS SEL(32, 64)
#define LREG SEL(lw, ld)
#define SREG SEL(sw, sd)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// register & pmp offsets
#define PC 0
#define RA 1
#define SP 2
#define GP 3
#define TP 4
#define T0 5
#define T1 6
#define T2 7
#define S0 8
#define S1 9
#define A0 10
#define A1 11
#define A2 12
#define A3 13
#define A4 14
#define A5 15
#define A6 16
#define A7 17
#define S2 18
#define S3 19
#define S4 20
#define S5 21
#define S6 22
#define S7 23
#define S8 24
#define S9 25
#define S10 26
#define S11 27
#define T3 28
#define T4 29
#define T5 30
#define T6 31

#ifdef RV32
#define PMPCFG0 32
#define PMPCFG1 33
#define PMPADDR0 34
#define PMPADDR1 35
#define PMPADDR2 36
#define PMPADDR3 37
#define PMPADDR4 38
#define PMPADDR5 39
#define PMPADDR6 40
#define PMPADDR7 41
#else /* RV64 */
#define PMPCFG0 32
#define PMPADDR0 33
#define PMPADDR1 34
#define PMPADDR2 35
#define PMPADDR3 36
#define PMPADDR4 37
#define PMPADDR5 38
#define PMPADDR6 39
#define PMPADDR7 40
#endif

#define INST_ECALL 0x00000073
#define INST_URET 0x00200073

/*** Machine CSR Numbers **/
/* Machine Information Registers */
#define CSR_MVENDORID 0xF11
#define CSR_MARCHID 0xF12
#define CSR_MIMPID 0xF13
#define CSR_MHARTID 0xF14
/* Machine Trap Setup */
#define CSR_MSTATUS 0x300
#define CSR_MISA 0x301
#define CSR_MEDELEG 0x302
#define CSR_MIDELEG 0x303
#define CSR_MIE 0x304
#define CSR_MTVEC 0x305
#define CSR_MCOUNTEREN 0x306
#define CSR_MSTATUSH 0x310
/* Machine Trap Handling */
#define CSR_MSCRATCH 0x340
#define CSR_MEPC 0x341
#define CSR_MCAUSE 0x342
#define CSR_MTVAL 0x343
#define CSR_MIP 0x344
/* Machine Memory Protection */
#define CSR_PMPCFG0 0x3A0
#define CSR_PMPCFG1 0x3A1

#define CSR_PMPADDR0 0x3B0
#define CSR_PMPADDR1 0x3B1
#define CSR_PMPADDR2 0x3B2
#define CSR_PMPADDR3 0x3B3
#define CSR_PMPADDR4 0x3B4
#define CSR_PMPADDR5 0x3B5
#define CSR_PMPADDR6 0x3B6
#define CSR_PMPADDR7 0x3B7
/* Machine Counter/Timers */
#define CSR_MCYCLE 0xB00
#define CSR_MINSTRET 0xB02
#define CSR_MHPMCOUNTER3 0xB03
#define CSR_MHPMCOUNTER4 0xB04
#define CSR_MHPMCOUNTER5 0xB05
#define CSR_MHPMCOUNTER6 0xB06
#define CSR_MHPMCOUNTER7 0xB07
#define CSR_MHPMCOUNTER8 0xB08
#define CSR_MHPMCOUNTER9 0xB09
#define CSR_MHPMCOUNTER10 0xB0A
#define CSR_MHPMCOUNTER11 0xB0B
#define CSR_MHPMCOUNTER12 0xB0C
#define CSR_MHPMCOUNTER13 0xB0D
#define CSR_MHPMCOUNTER14 0xB0E
#define CSR_MHPMCOUNTER15 0xB0F
#define CSR_MHPMCOUNTER16 0xB10
#define CSR_MHPMCOUNTER17 0xB11
#define CSR_MHPMCOUNTER18 0xB12
#define CSR_MHPMCOUNTER19 0xB13
#define CSR_MHPMCOUNTER20 0xB14
#define CSR_MHPMCOUNTER21 0xB15
#define CSR_MHPMCOUNTER22 0xB16
#define CSR_MHPMCOUNTER23 0xB17
#define CSR_MHPMCOUNTER24 0xB18
#define CSR_MHPMCOUNTER25 0xB19
#define CSR_MHPMCOUNTER26 0xB1A
#define CSR_MHPMCOUNTER27 0xB1B
#define CSR_MHPMCOUNTER28 0xB1C
#define CSR_MHPMCOUNTER29 0xB1D
#define CSR_MHPMCOUNTER30 0xB1E
#define CSR_MHPMCOUNTER31 0xB1F
#define CSR_MCYCLEH 0xB80
#define CSR_MINSTRETH 0xB82
#define CSR_MHPMCOUNTER3H 0xB83
#define CSR_MHPMCOUNTER4H 0xB84
#define CSR_MHPMCOUNTER5H 0xB85
#define CSR_MHPMCOUNTER6H 0xB86
#define CSR_MHPMCOUNTER7H 0xB87
#define CSR_MHPMCOUNTER8H 0xB88
#define CSR_MHPMCOUNTER9H 0xB89
#define CSR_MHPMCOUNTER10H 0xB8A
#define CSR_MHPMCOUNTER11H 0xB8B
#define CSR_MHPMCOUNTER12H 0xB8C
#define CSR_MHPMCOUNTER13H 0xB8D
#define CSR_MHPMCOUNTER14H 0xB8E
#define CSR_MHPMCOUNTER15H 0xB8F
#define CSR_MHPMCOUNTER16H 0xB90
#define CSR_MHPMCOUNTER17H 0xB91
#define CSR_MHPMCOUNTER18H 0xB92
#define CSR_MHPMCOUNTER19H 0xB93
#define CSR_MHPMCOUNTER20H 0xB94
#define CSR_MHPMCOUNTER21H 0xB95
#define CSR_MHPMCOUNTER22H 0xB96
#define CSR_MHPMCOUNTER23H 0xB97
#define CSR_MHPMCOUNTER24H 0xB98
#define CSR_MHPMCOUNTER25H 0xB99
#define CSR_MHPMCOUNTER26H 0xB9A
#define CSR_MHPMCOUNTER27H 0xB9B
#define CSR_MHPMCOUNTER28H 0xB9C
#define CSR_MHPMCOUNTER29H 0xB9D
#define CSR_MHPMCOUNTER30H 0xB9E
#define CSR_MHPMCOUNTER31H 0xB9F
/* Machine Counter Setup */
#define CSR_MCOUNTINHIBIT 0x320
#define CSR_MHPMEVENT3 0x323
#define CSR_MHPMEVENT4 0x324
#define CSR_MHPMEVENT5 0x325
#define CSR_MHPMEVENT6 0x326
#define CSR_MHPMEVENT7 0x327
#define CSR_MHPMEVENT8 0x328
#define CSR_MHPMEVENT9 0x329
#define CSR_MHPMEVENT10 0x32a
#define CSR_MHPMEVENT11 0x32b
#define CSR_MHPMEVENT12 0x32c
#define CSR_MHPMEVENT13 0x32d
#define CSR_MHPMEVENT14 0x32e
#define CSR_MHPMEVENT15 0x32f
#define CSR_MHPMEVENT16 0x330
#define CSR_MHPMEVENT17 0x331
#define CSR_MHPMEVENT18 0x332
#define CSR_MHPMEVENT19 0x333
#define CSR_MHPMEVENT20 0x334
#define CSR_MHPMEVENT21 0x335
#define CSR_MHPMEVENT22 0x336
#define CSR_MHPMEVENT23 0x337
#define CSR_MHPMEVENT24 0x338
#define CSR_MHPMEVENT25 0x339
#define CSR_MHPMEVENT26 0x33a
#define CSR_MHPMEVENT27 0x33b
#define CSR_MHPMEVENT28 0x33c
#define CSR_MHPMEVENT29 0x33d
#define CSR_MHPMEVENT30 0x33e
#define CSR_MHPMEVENT31 0x33f

/* CSR offsets */
/** MCAUSE **/
/* exception codes */
#define MCAUSE_EXCPT_INSTRUCTION_ADDRESS_MISALIGNED 0
#define MCAUSE_EXCPT_INSTRUCTION_ACCESS_FAULT 1
#define MCAUSE_EXCPT_ILLEGAL_INSTRUCTION 2
#define MCAUSE_EXCPT_BREAKPOINT 3
#define MCAUSE_EXCPT_LOAD_ADDRESS_MISALIGNED 4
#define MCAUSE_EXCPT_LOAD_ACCESS_FAULT 5
#define MCAUSE_EXCPT_STORE_ADDRESS_MISALIGNED 6
#define MCAUSE_EXCPT_STORE_ACCESS_FAULT 7
#define MCAUSE_EXCPT_USER_ECALL 8
#define MCAUSE_EXCPT_SUPERVISOR_ECALL 9
#define MCAUSE_EXCPT_MACHINE_ECALL 11
#define MCAUSE_EXCPT_INSTRUCTION_PAGE_FAULT 12
#define MCAUSE_EXCPT_LOAD_PAGE_FAULT 13
#define MCAUSE_EXCPT_STORE_PAGE_FAULT 15
/* interrupt codes */
#define MCAUSE_INTRP_USER_SOFTWARE 0
#define MCAUSE_INTRP_USER_TIMER 4
#define MCAUSE_INTRP_USER_EXTERN 8
#define MCAUSE_INTRP_SUPERVISOR_SOFTWARE 1
#define MCAUSE_INTRP_SUPERVISOR_TIMER 5
#define MCAUSE_INTRP_SUPERVISOR_EXTERN 9
#define MCAUSE_INTRP_MACHINE_SOFTWARE 3
#define MCAUSE_INTRP_MACHINE_TIMER 7
#define MCAUSE_INTRP_MACHINE_EXTERN 11

/* User CSR registers */
#define CSR_USTATUS 0x000
#define CSR_UIE 0x004
#define CSR_UTVEC 0x005
#define CSR_USCRATCH 0x040
#define CSR_UEPC 0x041
#define CSR_UCAUSE 0x042
#define CSR_UTVAL 0x043
#define CSR_UIP 0x044

/* User CSR fields. */
#define USTATUS_UIE 0x1
#define USTATUS_UPIE 0x10
