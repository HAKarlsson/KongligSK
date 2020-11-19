# This make files directory
MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CWD := $(notdir $(patsubst %/,%,$(dir $(MAKEFILE_PATH))))
# Elf directory
ELF_DIR = elf
ELF=$(ELF_DIR)/konglig.elf
# Configuration file for KongligSK.
CONFIG=config.yaml
# Linker script for KongligSK.
KONGLIG_LDS=konglig.lds
# Path to base directory of KongligSK repository.
KONGLIG_DIR = ..

.PHONY: all
all: konglig

$(ELF_DIR):
	mkdir -p $@

.PHONY: konglig
konglig: $(ELF_DIR) 
	make -C $(KONGLIG_DIR) all ELF_DIR=$(CWD)/$(ELF_DIR) CONFIG=$(CWD)/$(CONFIG) LDS=$(CWD)/$(KONGLIG_LDS)

.PHONY: clean
clean:
	make -C $(KONGLIG_DIR) clean
