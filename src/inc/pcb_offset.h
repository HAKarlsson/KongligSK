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
#ifndef KSK_REG_OFFSET_H
#define KSK_REG_OFFSET_H
#include "util.h"

#define PCB_PC (REG_BYTES * 0)
#define PCB_RA (REG_BYTES * 1)
#define PCB_SP (REG_BYTES * 2)
#define PCB_GP (REG_BYTES * 3)
#define PCB_TP (REG_BYTES * 4)
#define PCB_T0 (REG_BYTES * 5)
#define PCB_T1 (REG_BYTES * 6)
#define PCB_T2 (REG_BYTES * 7)
#define PCB_S0 (REG_BYTES * 8)
#define PCB_S1 (REG_BYTES * 9)
#define PCB_A0 (REG_BYTES * 10)
#define PCB_A1 (REG_BYTES * 11)
#define PCB_A2 (REG_BYTES * 12)
#define PCB_A3 (REG_BYTES * 13)
#define PCB_A4 (REG_BYTES * 14)
#define PCB_A5 (REG_BYTES * 15)
#define PCB_A6 (REG_BYTES * 16)
#define PCB_A7 (REG_BYTES * 17)
#define PCB_S2 (REG_BYTES * 18)
#define PCB_S3 (REG_BYTES * 19)
#define PCB_S4 (REG_BYTES * 20)
#define PCB_S5 (REG_BYTES * 21)
#define PCB_S6 (REG_BYTES * 22)
#define PCB_S7 (REG_BYTES * 23)
#define PCB_S8 (REG_BYTES * 24)
#define PCB_S9 (REG_BYTES * 25)
#define PCB_S10 (REG_BYTES * 26)
#define PCB_S11 (REG_BYTES * 27)
#define PCB_T3 (REG_BYTES * 28)
#define PCB_T4 (REG_BYTES * 29)
#define PCB_T5 (REG_BYTES * 30)
#define PCB_T6 (REG_BYTES * 31)

#define PCB_PMPCFG0 (REG_BYTES * 32)
#define PCB_PMPADDR0 (REG_BYTES * 33)
#define PCB_PMPADDR1 (REG_BYTES * 34)
#define PCB_PMPADDR2 (REG_BYTES * 35)
#define PCB_PMPADDR3 (REG_BYTES * 36)
#define PCB_PMPADDR4 (REG_BYTES * 37)
#define PCB_PMPADDR5 (REG_BYTES * 38)
#define PCB_PMPADDR6 (REG_BYTES * 39)
#define PCB_PMPADDR7 (REG_BYTES * 40)

#endif /* KSK_REG_OFFSET_H */
