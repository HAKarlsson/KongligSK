# SPDX-License-Identifier: GPL-3.0-only
# Copyright 2020, Henrik Karlsson

# C (gcc) flags
CFLAGS	+= -I$(HDR_DIR)
CFLAGS	+= -mabi=lp64 -march=rv64iac
#CFLAGS	+= -mabi=ilp32 -march=rv32iac
CFLAGS	+= -mcmodel=medany
CFLAGS	+= -Wall -Werror -Wextra
CFLAGS  += -Wno-unused-parameter
CFLAGS	+= -fno-stack-protector -fno-asynchronous-unwind-tables
CFLAGS	+= -Wstrict-prototypes -Wmissing-prototypes
CFLAGS	+= -Wmissing-declarations
CFLAGS	+= -Wundef -Wpointer-arith -ffreestanding
CFLAGS  += -fomit-frame-pointer -Wstack-usage=256
CFLAGS	+= -std=c99
CFLAGS	+= -O2 -g
# Don't modify t0-t6
CFLAGS	+= -ffixed-t0 -ffixed-t1 -ffixed-t2 -ffixed-t3
CFLAGS	+= -ffixed-t4 -ffixed-t5 -ffixed-t6

# Assembly (gcc) flags
SFLAGS	+= -I$(HDR_DIR)
SFLAGS	+= -D__ASSEMBLER__
SFLAGS	+= -mabi=lp64 -march=rv64iac
#SFLAGS	+= -mabi=ilp32 -march=rv32iac
SFLAGS	+= -g

# Linker (ld) flags
LDFLAGS += -nostdlib -T$(LDS)
LDFLAGS += --relax -O2
