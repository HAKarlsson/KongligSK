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
        /* 64 KiB rom */
        rom (rxai!w) : ORIGIN = rom, LENGTH = 0x2000
        /* 4 KiB ram */
        ram (wxa!ri) : ORIGIN = ram, LENGTH = 0x1000 
}

SECTIONS
{
        /* 1 KiB stack */
        __stack_size = DEFINED(__stack_size) ? __stack_size : 0x200;
        PROVIDE(__stack_size = __stack_size);

        .text : {
                KEEP(*(.text.init))
                KEEP(*(.text.entry))
                *(.text)
                *(.text.*)
                . = ALIGN(8); 
        } >rom AT>rom

        .data : ALIGN(8) {
                *(.data)
                *(.data.*)
                *(.sdata)
                *(.sdata.*)
                *(.rodata .rodata.*)
                *(.rdata .rdata.*)
                . = ALIGN(8); 
        } >ram AT>rom

        PROVIDE(__global_pointer$ = ADDR(.data)); 
        PROVIDE(_data_lma = LOADADDR(.data)); 
        PROVIDE(_data = ADDR(.data)); 
        PROVIDE(_edata = ADDR(.data) + SIZEOF(.data)); 

        .bss : ALIGN(8) {
                *(.bss)
                *(.bss.*)
                *(.sbss*)
                *(COMMON)
                . = ALIGN(8); 
        } >ram AT>ram
        PROVIDE(_bss = ADDR(.bss)); 
        PROVIDE(_ebss = ADDR(.bss) + SIZEOF(.bss)); 

        .stack ORIGIN(ram) + LENGTH(ram) - __stack_size : {
            . += __stack_size;
        } >ram AT>ram
        PROVIDE(_sp = ADDR(.stack) + SIZEOF(.stack));
}
