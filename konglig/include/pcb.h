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
#ifndef _PCB_H
#define _PCB_H
#include "types.h"

/* General registers offset */
#define GR_PC       0
#define GR_RA       1
#define GR_SP       2
#define GR_GP       3
#define GR_TP       4
#define GR_T0       5
#define GR_T1       6
#define GR_T2       7
#define GR_S0       8
#define GR_S1       9
#define GR_A0       10
#define GR_A1       11
#define GR_A2       12
#define GR_A3       13
#define GR_A4       14
#define GR_A5       15
#define GR_A6       16
#define GR_A7       17
#define GR_S2       18
#define GR_S3       19
#define GR_S4       20
#define GR_S5       21
#define GR_S6       22
#define GR_S7       23
#define GR_S8       24
#define GR_S9       25
#define GR_S10      26
#define GR_S11      27
#define GR_T3       28
#define GR_T4       29
#define GR_T5       30
#define GR_T6       31

/* Trap registers offset */
#define TR_USTATUS  0
#define TR_UIE      1
#define TR_UTVEC    2
#define TR_USCRATCH 3
#define TR_UEPC     4
#define TR_UCAUSE   5
#define TR_UTVAL    6
#define TR_UIP      7

typedef struct pcb {
    /* General registers */
    uintptr_t gr[32];
    /* Trap setup and handling registers */
    uintptr_t tr[8];
} pcb_t;

#endif /* _PCB_H */
