# This file is part of KongligSK.
# Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
# 
# KongligSK is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# KongligSK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.

# Tools
CC = riscv64-unknown-elf-gcc
OBJDUMP = riscv64-unknown-elf-objdump
SIZE = riscv64-unknown-elf-size

BUILDDIR ?= konglig_build

SRCDIR    = src
HDRDIR    = include
ELF       = $(BUILDDIR)/konglig.elf
C_SOURCE  = $(wildcard $(SRCDIR)/*.c)
S_SOURCE  = $(wildcard $(SRCDIR)/*.S)
C_OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCE))
S_OBJECTS = $(patsubst $(SRCDIR)/%.S, $(BUILDDIR)/%.o, $(S_SOURCE))
HEADERS   = $(wildcard $(HDRDIR)/*.h)
	    

### C flags ###
C_FLAGS += -std=c99 
C_FLAGS += -Iinclude
C_FLAGS += -Wall -Wextra -Wno-unused-parameter
C_FLAGS += -Og -g

### Assembly flags ###
# __ASSEMBLER__ is already defined for GCC, 
# but maybe not other compilers.
S_FLAGS += -D__ASSEMBLER__
S_FLAGS += -Iinclude
S_FLAGS += -Wall
S_FLAGS += -g

### Linker flags ###
LD_FLAGS += -nostdlib
LD_FLAGS += -T $(MEMORY)
LD_FLAGS += -T konglig.lds



# Build rules
.PHONY: all
all: $(BUILDDIR) $(ELF)

.PHONY: clean
clean: 
	@rm -fr $(BUILDDIR)

tags: $(wildcard src/*) $(wildcard include/*)
	@echo Generating tags for src/ and include/...
	@ctags -R src/ include/
	@echo Done.

$(BUILDDIR): 
	@mkdir -p $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(C_FLAGS) -c $< -o $@
	$(OBJDUMP) -d $@ > $@.da


$(BUILDDIR)/%.o: $(SRCDIR)/%.S $(HEADERS)
	$(CC) $(S_FLAGS) -c $< -o $@
	$(OBJDUMP) -d $@ > $@.da

$(ELF): $(S_OBJECTS) $(C_OBJECTS)
	$(CC) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o $@
	$(OBJDUMP) -d $@ > $@.da
	$(SIZE) $(S_OBJECTS) $(C_OBJECTS) $(ELF)
