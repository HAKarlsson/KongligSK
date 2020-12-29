# SPDX-License-Identifier: GPL-3.0-only
# Copyright 2020, Henrik Karlsson

ARCH	= rv64iac
ABI     = lp64

# C (gcc) flags
CFLAGS	+= -I$(HDR_DIR)
CFLAGS	+= -mabi=$(ABI) -march=$(ARCH)
CFLAGS	+= -mcmodel=medany
CFLAGS	+= -Wall -Werror -Wextra
CFLAGS  += -Wno-unused-parameter
CFLAGS	+= -fno-stack-protector -fno-asynchronous-unwind-tables
CFLAGS	+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS	+= -Wmissing-declarations
CFLAGS	+= -Wundef -Wpointer-arith -ffreestanding
#CFLAGS  += -fomit-frame-pointer -Wstack-usage=256
CFLAGS	+= -std=c99
CFLAGS	+= -O2 -g
# Don't modify t0-t6
CFLAGS	+= -ffixed-t0 -ffixed-t1 -ffixed-t2 -ffixed-t3
CFLAGS	+= -ffixed-t4 -ffixed-t5 -ffixed-t6
CFLAGS	+= -ffixed-s0 -ffixed-s1 -ffixed-s2 -ffixed-s3
CFLAGS	+= -ffixed-s4 -ffixed-s5 -ffixed-s6 -ffixed-s7
CFLAGS	+= -ffixed-s8 -ffixed-s9 -ffixed-s10 -ffixed-s11

# Assembly (gcc) flags
SFLAGS	+= -I$(HDR_DIR)
SFLAGS	+= -D__ASSEMBLER__
SFLAGS	+= -mabi=$(ABI) -march=$(ARCH)
SFLAGS	+= -g

# Linker (ld) flags
LDFLAGS += -nostdlib 
LDFLAGS += $(addprefix -T, $(LDS))
LDFLAGS += --relax -O2
