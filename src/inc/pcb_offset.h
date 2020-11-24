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
#pragma once
#include "util.h"

#define PCB_PC (REGBYTES * 0)
#define PCB_RA (REGBYTES * 1)
#define PCB_SP (REGBYTES * 2)
#define PCB_GP (REGBYTES * 3)
#define PCB_TP (REGBYTES * 4)
#define PCB_T0 (REGBYTES * 5)
#define PCB_T1 (REGBYTES * 6)
#define PCB_T2 (REGBYTES * 7)
#define PCB_S0 (REGBYTES * 8)
#define PCB_S1 (REGBYTES * 9)
#define PCB_A0 (REGBYTES * 10)
#define PCB_A1 (REGBYTES * 11)
#define PCB_A2 (REGBYTES * 12)
#define PCB_A3 (REGBYTES * 13)
#define PCB_A4 (REGBYTES * 14)
#define PCB_A5 (REGBYTES * 15)
#define PCB_A6 (REGBYTES * 16)
#define PCB_A7 (REGBYTES * 17)
#define PCB_S2 (REGBYTES * 18)
#define PCB_S3 (REGBYTES * 19)
#define PCB_S4 (REGBYTES * 20)
#define PCB_S5 (REGBYTES * 21)
#define PCB_S6 (REGBYTES * 22)
#define PCB_S7 (REGBYTES * 23)
#define PCB_S8 (REGBYTES * 24)
#define PCB_S9 (REGBYTES * 25)
#define PCB_S10 (REGBYTES * 26)
#define PCB_S11 (REGBYTES * 27)
#define PCB_T3 (REGBYTES * 28)
#define PCB_T4 (REGBYTES * 29)
#define PCB_T5 (REGBYTES * 30)
#define PCB_T6 (REGBYTES * 31)

#define PCB_PMPADDR0 (REGBYTES * 32)
#define PCB_PMPADDR1 (REGBYTES * 33)
#define PCB_PMPADDR2 (REGBYTES * 34)
#define PCB_PMPADDR3 (REGBYTES * 35)
#define PCB_PMPADDR4 (REGBYTES * 36)
#define PCB_PMPADDR5 (REGBYTES * 37)
#define PCB_PMPADDR6 (REGBYTES * 38)
#define PCB_PMPADDR7 (REGBYTES * 39)
#define PCB_PMPCFG0 (REGBYTES * 40)
#ifdef RV32
#define PCB_PMPCFG1 (REGBYTES * 41)
#endif
