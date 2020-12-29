# SPDX-License-Identifier: GPL-3.0-only
# Copyright 2020, Henrik Karlsson

# Toolchain
PREFIX ?= riscv64-elf-
CC	= $(PREFIX)gcc
LD	= $(PREFIX)ld
OBJDUMP	= $(PREFIX)objdump
SIZE	= $(PREFIX)size

CLOC    = cloc

# Build directory
BUILD  ?= build
SRC_DIR	= src
HDR_DIR = inc

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*.S)
HDRS = $(wildcard $(HDR_DIR)/*.h)
OBJS = $(patsubst $(SRC_DIR)/%, $(BUILD)/%.o, $(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%, $(BUILD)/%.d, $(SRCS))
LDS  = memory.lds konglig.lds
ELF  = $(BUILD)/konglig.elf
DAS  = $(patsubst $(BUILD)/%, $(BUILD)/%.da, $(OBJS) $(ELF))


include flags.mk

.PHONY: all clean size
.PRECIOUS: $(OBJS)

all: $(ELF) $(DAS)

clean:
	rm -f $(OBJS) $(ELF) $(DAS) $(DEPS)

size:
	$(SIZE) $(OBJS) $(ELF)

cloc:
	$(CLOC) $(HDRS) $(SRCS)

$(BUILD):
	mkdir -p $@

$(BUILD)/%.c.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -MD -c -o $@ $<

$(BUILD)/%.S.o: $(SRC_DIR)/%.S | $(BUILD)
	$(CC) $(SFLAGS) -MD -c -o $@ $<

$(BUILD)/%.elf: $(OBJS) $(LDS) | $(BUILD)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(BUILD)/%.da: $(BUILD)/% | $(BUILD)
	$(OBJDUMP) -d $< > $@


-include $(DEPS)
