// SPDX-License-Identifier: GPL-2.0-only
// Copyright 2020, Saab AB
// Macros for configuring the partitions.
// Taken and adapted from github.com/castor-software/openmz config_macro.h
#pragma once

// clang-format off
#define __PART(PC,							\
		CFG0, ADDR0, CFG1, ADDR1, CFG2, ADDR2, CFG3, ADDR3,	\
		CFG4, ADDR4, CFG5, ADDR5, CFG6, ADDR6, CFG7, ADDR7)	\
{									\
	.regs.pc = PC,							\
	.pmp = {							\
		.cfg0 = CFG0 | CFG1 << 8 | CFG2 << 16 | CFG3 << 24,	\
		.cfg1 = CFG4 | CFG5 << 8 | CFG6 << 16 | CFG7 << 24,	\
		.addr0 = ADDR0,						\
		.addr1 = ADDR1,						\
		.addr2 = ADDR2,						\
		.addr3 = ADDR3,						\
		.addr4 = ADDR4,						\
		.addr5 = ADDR5,						\
		.addr6 = ADDR6,						\
		.addr7 = ADDR7,						\
	}								\
},

#define PART8(pc, pmp0, pmp1, pmp2, pmp3, pmp4, pmp5, pmp6, pmp7) \
	__PART(pc, pmp0, pmp1, pmp2, pmp3, pmp4, pmp5, pmp6, pmp7) 
#define PART7(pc, pmp0, pmp1, pmp2, pmp3, pmp4, pmp5, pmp6) \
	__PART(pc, pmp0, pmp1, pmp2, pmp3, pmp4, pmp5, pmp6, 0,0) 
#define PART6(pc, pmp0, pmp1, pmp2, pmp3, pmp4, pmp5) \
	__PART(pc, pmp0, pmp1, pmp2, pmp3, pmp4, pmp5, 0,0, 0,0) 
#define PART5(pc, pmp0, pmp1, pmp2, pmp3, pmp4) \
	__PART(pc, pmp0, pmp1, pmp2, pmp3, pmp4, 0,0, 0,0, 0,0) 
#define PART4(pc, pmp0, pmp1, pmp2, pmp3) \
	__PART(pc, pmp0, pmp1, pmp2, pmp3, 0,0, 0,0, 0,0, 0,0) 
#define PART3(pc, pmp0, pmp1, pmp2) \
	__PART(pc, pmp0, pmp1, pmp2, 0,0, 0,0, 0,0, 0,0, 0,0) 
#define PART2(pc, pmp0, pmp1) \
	__PART(pc, pmp0, pmp1, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0) 
#define PART1(pc, pmp0) \
	__PART(pc, pmp0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0) 

// Some of these probably don't make sense
#define W 2
#define RW 3
#define X 4
#define RX 5
#define WX 6
#define RWX 7

// We probably will remove TOR, allowing us to easier move PMP regions between zones.
#define TOR(rwx, addr) (0x8 | rwx), (addr >> 2)
#define NA4(rwx, addr) (0x10 | rwx), (addr >> 2)
#define NAPOT(rwx, addr, size) (0x18 | rwx), (((addr >> 2) | ((1 << (size - 2)) - 1)) & ~(1 << (size - 2)))
