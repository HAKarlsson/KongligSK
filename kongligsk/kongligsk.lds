/* SPDX-License-Identifier: GPL-3.0-only */
/* Copyright 2020-2021, Henrik Karlsaon */
OUTPUT_ARCH("riscv")

ENTRY(_start)

MEMORY {
	RAM(rwx) : ORIGIN = 0x80000000, LENGTH = 0x1000
}

SECTIONS {
	.text : {
		KEEP(*(.text.init))
		KEEP(*(.text.traps))
		KEEP(*(.text.switch))
		*(.text) 
		*(.text.*)
	}
	
	.data : {
		. = ALIGN(64 / 8);
		PROVIDE(__global_pointer$ = . + 0x400);
		*(.data) 
		*(.data.*) 
		*(.rodata) 
		*(.rodata.*)
	}
	
	.bss : {
		. = ALIGN(64 / 8);
		*(.bss) 
		*(.bss.*)
	}
	
	PROVIDE(__stack_size = 0x100);
	.stack : {
		. = ALIGN(16) + __stack_size;
		PROVIDE(__stack_pointer$ = .);
	}
}
