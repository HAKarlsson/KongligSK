# SPDX-License-Identifier: GPL-3.0-only
# Copyright 2020-2021, Henrik Karlsson

# Arch (RV64 or RV32)
ARCH	?= RV64
# Toolchain prefix
PREFIX	?= riscv64-elf-
# Build directory for object, elf and da.
BUILD	?= build

# Toolchain
CC	= $(PREFIX)gcc
LD	= $(PREFIX)ld
AR	= $(PREFIX)ar
OBJDUMP	= $(PREFIX)objdump
SIZE	= $(PREFIX)size

CLOC	= cloc
FORMAT	= clang-format

# Files
SRCS	= $(wildcard kongligsk/*.c) $(wildcard kongligsk/*.S)
HDRS	= $(wildcard kongligsk/*.h)
LDS	= kongligsk/kongligsk.lds

# Targets
OBJS	= $(patsubst %, $(BUILD)/%.o, $(SRCS))
DEPS	= $(patsubst %, $(BUILD)/%.d, $(SRCS))
ELF	= $(BUILD)/kongligsk.elf
DAS	= $(addsuffix .da, $(OBJS) $(ELF))


include FLAGS.mk

.PHONY: all clean cloc format size
.PRECIOUS: $(OBJS)

all: $(ELF) $(DAS)

clean:
	rm -f $(OBJS) $(ELF) $(DAS) $(DEPS)

size: $(OBJS) $(ELF)
	$(SIZE) $(OBJS) $(ELF)

cloc:
	$(CLOC) $(HDRS) $(SRCS)

format:
	$(FORMAT) -i kongligsk/*.[hc]

$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MD -c -o $@ $<

$(BUILD)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(SFLAGS) -MD -c -o $@ $<

$(ELF): $(OBJS) $(LDS)
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

%.da: %
	$(OBJDUMP) -d $< > $@


-include $(DEPS)
