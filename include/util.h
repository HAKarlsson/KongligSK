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
#ifndef _UTIL_H
#define _UTIL_H

#define NO_RETURN __attribute__ ((noreturn))
#define ALWAYS_INLINE __attribute__ ((always_inline))
#define HOT __attribute__ ((cold))
#define COLD __attribute__ ((cold))


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/* Use a on RV32, b on RV64 */
#if __riscv_xlen == 32
#define SEL(a, b) a
#else
#define SEL(a, b) b
#endif

#define SREG        SEL(sw, sd)
#define LREG        SEL(lw, ld)
#define REG_BYTES   SEL(4, 8)
#define REG_BITS    SEL(32, 64)

#define ONES        SEL(0xFFFFFFFFUL, 0xFFFFFFFFFFFFFFFFUL) 

/* Set bit n. */
#define BIT(n)      (1 << (n))
/* Set bits n, n+1, ..., m-1. */
#define BITS(n,m)   (0)

#endif /* _UTIL_H */
