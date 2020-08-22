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
#ifndef KSK_CSR_H
#define KSK_CSR_H
#include "util.h"

#ifndef __ASSEMBLER__
/*** CSR functions for C ***/
/* Base instructions */
#define CSRRW(rd, csr_num, rs)                                                 \
  __asm__("csrrw %0, %1, %2" : "=r"(rd) : "I"(csr_num), "r"(rs))

#define CSRRS(rd, csr_num, rs)                                                 \
  __asm__("csrrs %0, %1, %2" : "=r"(rd) : "I"(csr_num), "r"(rs))

#define CSRRC(rd, csr_num, rs)                                                 \
  __asm__("csrrc %0, %1, %2" : "=r"(rd) : "I"(csr_num), "r"(rs))

#define CSRRWI(rd, csr_num, imm)                                               \
  __asm__("csrrwi %0, %1, %2" : "=r"(rd) : "I"(csr_num), "I"(imm))

#define CSRRSI(rd, csr_num, imm)                                               \
  __asm__("csrrsi %0, %1, %2" : "=r"(rd) : "I"(csr_num), "I"(imm))

#define CSRRCI(rd, csr_num, imm)                                               \
  __asm__("csrrci %0, %1, %2" : "=r"(rd) : "I"(csr_num), "I"(imm))

/* Pseudo CSR instructions */
#define CSRR(rd, csr_num) __asm__("csrrs %0, %1, x0" : "=r"(rd) : "I"(csr_num))

#define CSRW(csr_num, rs) __asm__("csrrw x0, %0, %1" ::"I"(csr_num), "r"(rs))

#define CSRS(csr_num, rs) __asm__("csrrs x0, %0, %1" ::"I"(csr_num), "r"(rs))

#define CSRC(csr_num, rs) __asm__("csrrs x0, %0, %1" ::"I"(csr_num), "r"(rs))

#define CSRWI(csr_num, imm)                                                    \
  __asm__("csrrwi x0, %0, %1" ::"I"(csr_num), "I"(imm))

#define CSRSI(csr_num, imm)                                                    \
  __asm__("csrrsi x0, %0, %1" ::"I"(csr_num), "I"(imm))

#define CSRCI(csr_num, imm)                                                    \
  __asm__("csrrsi x0, %0, %1" ::"I"(csr_num), "I"(imm))

#endif /* __ASSEMBLER__ */

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
#define CSR_MTINST 0x34A
#define CSR_MTVAL2 0x34B
/* Machine Memory Protection */
#define CSR_PMPCFG0 0x3A0
#define CSR_PMPCFG1 0x3A1
#define CSR_PMPCFG2 0x3A2
#define CSR_PMPCFG3 0x3A3
#define CSR_PMPCFG4 0x3A4
#define CSR_PMPCFG5 0x3A5
#define CSR_PMPCFG6 0x3A6
#define CSR_PMPCFG7 0x3A7
#define CSR_PMPCFG8 0x3A8
#define CSR_PMPCFG9 0x3A9
#define CSR_PMPCFG10 0x3AA
#define CSR_PMPCFG11 0x3AB
#define CSR_PMPCFG12 0x3AC
#define CSR_PMPCFG13 0x3AD
#define CSR_PMPCFG14 0x3AE
#define CSR_PMPCFG15 0x3AF
#define CSR_PMPADDR0 0x3B0
#define CSR_PMPADDR1 0x3B1
#define CSR_PMPADDR2 0x3B2
#define CSR_PMPADDR3 0x3B3
#define CSR_PMPADDR4 0x3B4
#define CSR_PMPADDR5 0x3B5
#define CSR_PMPADDR6 0x3B6
#define CSR_PMPADDR7 0x3B7
#define CSR_PMPADDR8 0x3B8
#define CSR_PMPADDR9 0x3B9
#define CSR_PMPADDR10 0x3BA
#define CSR_PMPADDR11 0x3BB
#define CSR_PMPADDR12 0x3BC
#define CSR_PMPADDR13 0x3BD
#define CSR_PMPADDR14 0x3BE
#define CSR_PMPADDR15 0x3BF
#define CSR_PMPADDR16 0x3C0
#define CSR_PMPADDR17 0x3C1
#define CSR_PMPADDR18 0x3C2
#define CSR_PMPADDR19 0x3C3
#define CSR_PMPADDR20 0x3C4
#define CSR_PMPADDR21 0x3C5
#define CSR_PMPADDR22 0x3C6
#define CSR_PMPADDR23 0x3C7
#define CSR_PMPADDR24 0x3C8
#define CSR_PMPADDR25 0x3C9
#define CSR_PMPADDR26 0x3CA
#define CSR_PMPADDR27 0x3CB
#define CSR_PMPADDR28 0x3CC
#define CSR_PMPADDR29 0x3CD
#define CSR_PMPADDR30 0x3CE
#define CSR_PMPADDR31 0x3CF
#define CSR_PMPADDR32 0x3D0
#define CSR_PMPADDR33 0x3D1
#define CSR_PMPADDR34 0x3D2
#define CSR_PMPADDR35 0x3D3
#define CSR_PMPADDR36 0x3D4
#define CSR_PMPADDR37 0x3D5
#define CSR_PMPADDR38 0x3D6
#define CSR_PMPADDR39 0x3D7
#define CSR_PMPADDR40 0x3D8
#define CSR_PMPADDR41 0x3D9
#define CSR_PMPADDR42 0x3DA
#define CSR_PMPADDR43 0x3DB
#define CSR_PMPADDR44 0x3DC
#define CSR_PMPADDR45 0x3DD
#define CSR_PMPADDR46 0x3DE
#define CSR_PMPADDR47 0x3DF
#define CSR_PMPADDR48 0x3E0
#define CSR_PMPADDR49 0x3E1
#define CSR_PMPADDR50 0x3E2
#define CSR_PMPADDR51 0x3E3
#define CSR_PMPADDR52 0x3E4
#define CSR_PMPADDR53 0x3E5
#define CSR_PMPADDR54 0x3E6
#define CSR_PMPADDR55 0x3E7
#define CSR_PMPADDR56 0x3E8
#define CSR_PMPADDR57 0x3E9
#define CSR_PMPADDR58 0x3EA
#define CSR_PMPADDR59 0x3EB
#define CSR_PMPADDR60 0x3EC
#define CSR_PMPADDR61 0x3ED
#define CSR_PMPADDR62 0x3EE
#define CSR_PMPADDR63 0x3EF
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
#define MCAUSE_INTERRUPT_BIT BIT(REG_BYTES - 1)

#define MCAUSE_INSTRUCTION_ADDRESS_MISALIGNED 0
#define MCAUSE_INSTRUCTION_ACCESS_FAULT 1
#define MCAUSE_ILLEGAL_INSTRUCTION 2
#define MCAUSE_BREAKPOINT 3
#define MCAUSE_LOAD_ADDRESS_MISALIGNED 4
#define MCAUSE_LOAD_ACCESS_FAULT 5
#define MCAUSE_STORE_ADDRESS_MISALIGNED 6
#define MCAUSE_STORE_ACCESS_FAULT 7
#define MCAUSE_UMODE_ECALL 8
#define MCAUSE_SMODE_ECALL 9
#define MCAUSE_MMODE_ECALL 11
#define MCAUSE_INSTRUCTION_PAGE_FAULT 12
#define MCAUSE_LOAD_PAGE_FAULT 13
#define MCAUSE_STORE_PAGE_FAULT 15

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

#endif /* KSK_CSR_H */
