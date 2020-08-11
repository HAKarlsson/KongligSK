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

CSRC = $(wildcard *.c)
SSRC = $(wildcard *.S)
OBJS = $(CSRC:%.c=%.o) $(SSRC:%.S=%.o)
DIR_OBJS = $(addprefix $(BUILD_DIR)/, $(OBJS))

CFLAGS += -std=c99 
CFLAGS += -Iinclude
CFLAGS += -Wall 
CFLAGS += -Og -g 

# __ASSEMBLER__ is already defined for GCC, 
# but maybe not other compilers.
SFLAGS += -D__ASSEMBLER__
SFLAGS += -Iinclude
SFLAGS += -Wall
# Do optimizations do anything to assembly code???
SFLAGS += -Og -g

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(CC) $(SFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: all
all: $(BUILD_DIR) $(DIR_OBJS)
	$(SIZE) -t $(DIR_OBJS)

.PHONY: clean
clean: 
	rm -f $(DIR_OBJS)
