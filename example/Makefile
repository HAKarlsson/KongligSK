
CWD = $(shell pwd)
ELF_DIR = $(CWD)/elf
ELF=$(ELF_DIR)/konglig.elf
KONGLIG_DIR = ..
CONFIG=$(PWD)/config.yaml
KONGLIG_LDS=$(PWD)/konglig.lds

.PHONY: all
all: kernel

$(ELF_DIR):
	mkdir -p $@

.PHONY: kernel
kernel: $(ELF_DIR) 
	make -C $(KONGLIG_DIR) all ELF=$(ELF) CONFIG=$(CONFIG) LDS=$(KONGLIG_LDS)
