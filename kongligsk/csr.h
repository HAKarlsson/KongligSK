// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#pragma once
// clang-format off

#define read_csr(csr) \
	({ unsigned long __tmp; asm volatile ("csrr %0, "#csr :"=r"(__tmp)); __tmp; })
#define write_csr(csr, val) \
	({ asm volatile ("csrw " #csr ", %0" :: "rK"(val)); })
#define swap_csr(csr, val) \
	({ unsigned long __tmp; asm volatile ("csrrw %0, " #csr ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })
#define set_csr(csr, val) \
	({ unsigned long __tmp; asm volatile ("csrrs %0, " #csr ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })
#define clear_csr(csr, val) \
	({ unsigned long __tmp; asm volatile ("csrrc %0, " #csr ", %1" : "=r"(__tmp) : "rK"(val)); __tmp; })

