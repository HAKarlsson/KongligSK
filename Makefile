

# Source and header directories
SRC_DIR	= src
HDR_DIR = src/inc

# Configuration file
CONFIG		?= example/config.yaml
# Linker script
LDS		?= example/konglig.lds
# Build directory
BUILD_DIR 	?= build
OBJ_DIR		?= $(BUILD_DIR)
DA_DIR		?= $(BUILD_DIR)
ELF_DIR		?= $(BUILD_DIR)
# RISC-V Toolchain prefix
RISCV_PREFIX	?= riscv64-unknown-elf-

# Configuration header
CONFIG_HDR	= $(HDR_DIR)/config.h
# ELF path
ELF		= $(ELF_DIR)/konglig.elf

# Source files, C and assembly
C_SRCS	= $(wildcard $(SRC_DIR)/*.c) 
S_SRCS	= $(wildcard $(SRC_DIR)/*.S)
# Object files
C_OBJS	= $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%.o, $(C_SRCS))
S_OBJS	= $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%.o, $(S_SRCS))
OBJS    = $(C_OBJS) $(S_OBJS)
HDRS	= $(wildcard $(HDR_DIR)/*.h) $(CONFIG_HDR)
# Disassembly files (objdump)
DAS	= $(patsubst $(OBJ_DIR)/%.o, $(DA_DIR)/%.da, $(OBJS)) \
	  $(patsubst $(ELF_DIR)/%.elf, $(DA_DIR)/%.elf.da, $(ELF))

# Toolchain
CC	= $(RISCV_PREFIX)gcc
LD	= $(RISCV_PREFIX)ld
OBJDUMP	= $(RISCV_PREFIX)objdump
SIZE	= $(RISCV_PREFIX)size

# C (gcc) flags
CFLAGS	= -I$(HDR_DIR)
CFLAGS	+= -mabi=lp64 -march=rv64imac -mcmodel=medany
CFLAGS	+= -Wall -Werror -Wextra 
CFLAGS	+= -Wno-unused-parameter
CFLAGS	+= -fno-stack-protector -fno-asynchronous-unwind-tables
CFLAGS	+= -Wstrict-prototypes -Wmissing-prototypes 
CFLAGS	+= -Wmissing-declarations
CFLAGS	+= -Wundef -Wpointer-arith -ffreestanding
CFLAGS	+= -fno-pic
#CFLAGS	+= -fstack-usage
CFLAGS	+= -std=c99 
CFLAGS	+= -O2 -g
# Assembly (gcc) flags
SFLAGS	+= -I$(HDR_DIR)
SFLAGS	+= -D__ASSEMBLER__
SFLAGS	+= -mabi=lp64 -march=rv64imac
SFLAGS	+= -fno-pic
SFLAGS	+= -g
# Linker (ld) flags
LDFLAGS += -nostdlib -T$(LDS)
LDFLAGS += --relax


.PHONY: all
all: $(BUILD_DIR) config elf disassembly

.PHONY: clean
clean: 
	rm -f $(DAS) $(OBJS) $(CONFIG_HDR)
	rm -rf $(BUILD_DIR)

.PHONY: config
config: $(CONFIG_HDR)

.PHONY: elf
elf: $(ELF)

.PHONY: disassembly 
disassembly: $(DAS)

.PHONY: da 
da: $(DAS)

.PHONY: format
format:
	clang-format -i --style=WebKit $(SRC_DIR)/*.c $(HDR_DIR)/*.h

.PHONY: size
size: $(OBJS) $(ELF)
	$(SIZE) $(OBJS) $(ELF)

.PHONY: cloc 
cloc:
	cloc $(HDRS) $(C_SRCS) $(S_SRCS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.S.o: $(SRC_DIR)/%.S $(HDRS)
	$(CC) $(SFLAGS) -c $< -o $@

$(DA_DIR)/%.da: $(OBJ_DIR)/%.o 
	$(OBJDUMP) -d $< > $@

$(DA_DIR)/%.elf.da: $(ELF_DIR)/%.elf
	$(OBJDUMP) -d $< > $@

# Format the file if we have clang-format
ifeq (,$(shell which clang-format))
$(CONFIG_HDR): $(CONFIG)
	tools/config.py $(CONFIG) > $(CONFIG_HDR)
else
$(CONFIG_HDR): $(CONFIG)
	tools/config.py $(CONFIG) | clang-format --style=WebKit > $(CONFIG_HDR)
endif

$(ELF_DIR)/%.elf: $(OBJS) $(LDS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
