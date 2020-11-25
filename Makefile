# This file is part of KongligSK.
# Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
#
# KongligSK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# KongligSK is distributed in the hope that it will be useful, # but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.

# Configuration file
CONFIG		?= example/config.yaml
# Linker script
LDS		?= example/konglig.lds
# Build directory
BUILD 		?= build
# RISC-V Toolchain prefix
RISCV_PREFIX	?= riscv64-unknown-elf-

# Source and header directories
SRC_DIR	= src
HDR_DIR = src/inc

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.S)
HDRS = $(wildcard $(HDR_DIR)/*.h)
# Object files
OBJS = $(patsubst $(SRC_DIR)/%, $(BUILD)/%.o, $(SRCS))
# Dependency files
DEPS = $(patsubst $(SRC_DIR)/%, $(BUILD)/%.d, $(SRCS))

# ELF file
ELF = $(BUILD)/konglig.elf
# Configuration header
CONFIG_H = $(HDR_DIR)/config.h

# Toolchain
CC	= $(RISCV_PREFIX)gcc
LD	= $(RISCV_PREFIX)ld
OBJDUMP	= $(RISCV_PREFIX)objdump
SIZE	= $(RISCV_PREFIX)size

# C (gcc) flags
CFLAGS	= -I$(HDR_DIR)
CFLAGS	+= -mabi=ilp32 -march=rv32iac -mcmodel=medany
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
SFLAGS	+= -mabi=ilp32 -march=rv32imac
SFLAGS	+= -g

# Linker (ld) flags
LDFLAGS += -nostdlib -T$(LDS)
LDFLAGS += --relax -O2
LDFLAGS += -melf32lriscv

.PHONY: all
all: config elf

.PHONY: clean
clean:
	rm -fr $(BUILD) $(CONFIG_H)

.PHONY: config
config: $(CONFIG_H)

.PHONY: elf
elf: $(ELF)

.PHONY: format
format:
	clang-format -i $(SRC_DIR)/*.c $(HDR_DIR)/*.h api/*.h

.PHONY: size
size: $(ELF) $(OBJS)
	$(SIZE) $(OBJS) $(ELF)

.PHONY: cloc
cloc:
	cloc $(HDRS) $(SRCS)

# Format the file if we have clang-format
ifeq (,$(shell which clang-format))
$(CONFIG_H): $(CONFIG)
	tools/config.py $< > $@
else
$(CONFIG_H): $(CONFIG)
	tools/config.py $< | clang-format > $@
endif

$(BUILD):
	@mkdir -p $@

$(BUILD)/%.c.o: $(SRC_DIR)/%.c $(CONFIG_H) | $(BUILD)
	$(CC) $(CFLAGS) -MMD -c $< -o $@
	$(OBJDUMP) -d $@ > $@.da

$(BUILD)/%.S.o: $(SRC_DIR)/%.S $(CONFIG_H) | $(BUILD)
	$(CC) $(SFLAGS) -MMD -c $< -o $@
	$(OBJDUMP) -d $@ > $@.da

$(BUILD)/%.elf: $(OBJS) $(LDS) | $(BUILD)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
	$(OBJDUMP) -d $@ > $@.da

-include $(DEPS)
