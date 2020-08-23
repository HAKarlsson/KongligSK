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
OUTPUT_ARCH("riscv")

ENTRY(_start)

MEMORY
{
        RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x1000
}

SECTIONS
{
        .text : {
                KEEP(*(.init))
                *(.text)
        }

        .data : ALIGN(8) {
                __global_pointer$ = . + 0x800; 
                *(.data.kernel)
                *(.data)
                *(.data.*)
                *(.rodata)
                *(.rodata.*)
        }

        __stack_top = ORIGIN(RAM) + LENGTH(RAM);
}
