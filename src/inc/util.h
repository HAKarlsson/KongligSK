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

#define NO_RETURN __attribute__((noreturn))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define REG_BYTES 8
#define REG_BITS 64

#define ONES 0xFFFFFFFFFFFFFFFFUL
#define MSb 0x8000000000000000UL

/* Set bit n. */
#define BIT(n) (1 << (n))
/* Set bits n, n+1, ..., m-1. */
#define BITS(n, m) ((ONES << (n)) & (ONES >>> (REG_BITS - (m))))
