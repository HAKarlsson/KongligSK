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

#define MSGS_LEN SEL(4, 2)

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

#define USTATUS 0
#define UIE 1
#define UTVEC 2
#define USCRATCH 3
#define UEPC 4
#define UCAUSE 5
#define UTVAL 6
#define UIP 7

typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef struct inbox {
  uintptr_t full;
  uintptr_t msgs[MSGS_LEN];
} Inbox;

/* PCB of a user-mode process. */
typedef struct process {
  uintptr_t regs[32];
  uint64_t pmpcfg0;
  uintptr_t pmpaddr[8];
  uintptr_t trap_regs[8];
  uintptr_t id;
} Process;

typedef struct kernel {
  Process processes[PROCESS_NUM];
  Inbox inboxes[PROCESS_NUM][PROCESS_NUM];
} Kernel;

extern Kernel kernel;

#endif /* KSK_KERNEL_H */
