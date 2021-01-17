# SPDX-License-Identifier: GPL-3.0-only
# Copyright 2020-2021, Henrik Karlsson

ifeq ($(ARCH),RV64)
	MARCH=rv64imac
	MABI=lp64
else ifeq ($(ARCH),RV32)
	MARCH=rv32imac
	MABI=ilp32
else
	$(error "Illegal ARCH. Must be RV32 or RV64.")
endif

# C (gcc) flags
CFLAGS	+= -mabi=$(MABI) -march=$(MARCH)
CFLAGS	+= -mcmodel=medany
CFLAGS	+= -Wall -Werror -Wextra
CFLAGS	+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS	+= -Wmissing-declarations
CFLAGS	+= -Wundef -Wpointer-arith -ffreestanding
CFLAGS  += -fomit-frame-pointer 
CFLAGS 	+= -Wstack-usage=128
CFLAGS  += -fstack-reuse=all
CFLAGS	+= -ffixed-t0 -ffixed-t1 -ffixed-t2 -ffixed-t3 -ffixed-t4 -ffixed-t5 -ffixed-t6
CFLAGS	+= -ffixed-s0 -ffixed-s1 -ffixed-s2 -ffixed-s3 -ffixed-s4 -ffixed-s5 -ffixed-s6 -ffixed-s7 -ffixed-s8 -ffixed-s9 -ffixed-s10 -ffixed-s11
CFLAGS	+= -O2 -g

# Assembly (gcc) flags
SFLAGS	+= -D__ASSEMBLER__
SFLAGS	+= -mabi=$(MABI) -march=$(MARCH)
SFLAGS	+= -g

# Linker (ld) flags
LDFLAGS	+= -nostdlib 
LDFLAGS	+= $(addprefix -T, $(LDS))
LDFLAGS	+= --relax -O2
