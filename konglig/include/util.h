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


#if __riscv_xlen == 32
#define SEL(a, b) a
#else
#define SEL(a, b) b
#endif

#define SREG    SEL(sw, sd)
#define LREG    SEL(lw, ld)
#define REG_SIZE SEL(4, 8)

#endif /* _UTIL_H */
