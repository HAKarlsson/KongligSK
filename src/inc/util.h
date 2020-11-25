/*
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 *
 * KongligSK is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * KongligSK is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with KongligSK.  If not, see
 * <https://www.gnu.org/licenses/>.
 */
#pragma once

#if __riscv_xlen == 32
#define RV32
#define SEL(x, y) x
#else
#define RV64
#define SEL(x, y) y
#endif

#ifdef __ASSEMBLER__
#define LREG SEL(lw, ld)
#define SREG SEL(sw, sd)
#else
#define LREG SEL("lw", "ld")
#define SREG SEL("sw", "sd")
#endif

#define REGBYTES SEL(4, 8)
#define REGBITS SEL(32, 64)

#define NO_RETURN __attribute__((noreturn))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
