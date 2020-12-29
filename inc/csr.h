// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020, Henrik Karlsson
#pragma once

#define CSRRW(rd, csr, rs) \
    __asm__ volatile("csrrw %0, " #csr ", %1" : "=r"(rd) : "r"(rs))

#define CSRRS(rd, csr, rs) \
    __asm__ volatile("csrrs %0, " #csr ", %1" : "=r"(rd) : "r"(rs))

#define CSRRC(rd, csr, rs) \
    __asm__ volatile("csrrc %0, " #csr ", %1" : "=r"(rd) : "r"(rs))

#define CSRRWI(rd, csr, imm) \
    __asm__ volatile("csrrwi %0, " #csr ", %1" : "=r"(rd) : "I"(imm))

#define CSRRSI(rd, csr, imm) \
    __asm__ volatile("csrrsi %0, " #csr ", %1" : "=r"(rd) : "I"(imm))

#define CSRRCI(rd, csr, imm) \
    __asm__ volatile("csrrci %0, " #csr ", %1" : "=r"(rd) : "I"(imm))

#define CSRR(rd, csr) __asm__ volatile("csrr %0, " #csr "" : "=r"(rd))

#define CSRW(csr, rs) __asm__ volatile("csrw " #csr ", %0" ::"r"(rs))

#define CSRS(csr, rs) __asm__ volatile("csrs " #csr ", %0" ::"r"(rs))

#define CSRC(csr, rs) __asm__ volatile("csrc " #csr ", %0" ::"r"(rs))

#define CSRWI(csr, imm) __asm__ volatile("csrwi " #csr ", %0" ::"I"(imm))

#define CSRSI(csr, imm) __asm__ volatile("csrsi " #csr ", %0" ::"I"(imm))

#define CSRCI(csr, imm) __asm__ volatile("csrci " #csr ", %0" ::"I"(imm))
