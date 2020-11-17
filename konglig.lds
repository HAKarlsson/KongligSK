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

MEMORY {
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x1000
}

SECTIONS {
    PROVIDE (__stack_size = 0x100);

    .text : {
        KEEP(*(.init))
        *(.text)
    }

    .data : ALIGN(8) {
        PROVIDE (__global_pointer$ = . + 0x800); 
        *(.data)
        *(.data.*)
        *(.rodata)
        *(.rodata.*)
    }

    .bss : ALIGN(8) {
        *(.bss)
        *(.bss.*)
    }
    .stack : {
        . = . + __stack_size;
        PROVIDE (__stack_top = .);
    }
}
