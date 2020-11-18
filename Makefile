# Configuration files
CONFIG_FILE?=example_config.yaml
# Build directory
BUILD_DIR?=build
# RISC-V Toolchain prefix
RISCV_PREFIX?=riscv64-unknown-elf-


# Source and header directories
SRC_DIR	= src
HDR_DIR = src/inc

ELF	?= $(BUILD_DIR)/konglig.elf
LDS	?= konglig.lds
CONFIG	?= example_config.yaml

CONFIG_HDR=$(HDR_DIR)/config.h

# Source files, C and assembly
C_SRCS	= $(wildcard $(SRC_DIR)/*.c) 
S_SRCS	= $(wildcard $(SRC_DIR)/*.S)
# Object files
C_OBJS	= $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%.o, $(C_SRCS))
S_OBJS	= $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%.o, $(S_SRCS))
OBJS    = $(C_OBJS) $(S_OBJS)
# Disassembly files (objdump)
DAS	= $(patsubst %.o, %.da, $(OBJS)) \
	  $(patsubst %.elf, %.da, $(ELF))

# Toolchain
CC	= $(RISCV_PREFIX)gcc
LD	= $(RISCV_PREFIX)ld
OBJDUMP	= $(RISCV_PREFIX)objdump

# C (gcc) flags
CFLAGS	= -I$(HDR_DIR)
CFLAGS	+= -mabi=lp64 -march=rv64imac -mcmodel=medany
CFLAGS	+= -Wall -Wextra -Wno-unused-parameter
CFLAGS	+= -std=c99
CFLAGS	+= -O2 -g
# Assembly (gcc) flags
SFLAGS	+= -I$(HDR_DIR)
SFLAGS	+= -D__ASSEMBLER__
SFLAGS	+= -mabi=lp64 -march=rv64imac -mcmodel=medany
SFLAGS	+= -O2 -g
# Linker (ld) flags
LDFLAGS = -nostdlib -T$(LDS)


.PHONY: all
all: $(BUILD_DIR) config elf disassembly 

.PHONY: clean
clean: 
	@rm -rf $(BUILD_DIR) $(CONFIG_HDR)

.PHONY: config
config: $(CONFIG_HDR)

.PHONY: elf
elf: $(ELF)

.PHONY: disassembly 
disassembly: $(DAS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c $(HDR_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S $(HDR_DIR)
	$(CC) $(SFLAGS) -c $< -o $@

%.da: %.o 
	$(OBJDUMP) -d $< > $@

%.da: %.elf
	$(OBJDUMP) -d $< > $@

$(CONFIG_HDR): $(CONFIG)
	tools/config.py $(CONFIG) > $(CONFIG_HDR); \

$(ELF): $(OBJS) $(LDS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
