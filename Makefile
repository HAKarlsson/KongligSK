

BUILD_DIR ?= $(CURDIR)/build-konglig

TOOLCHAIN_PREFIX ?= riscv64-unknown-elf-

CC = $(TOOLCHAIN_PREFIX)gcc
AS = $(TOOLCHAIN_PREFIX)as
SIZE = $(TOOLCHAIN_PREFIX)size

.PHONY: konglig
konglig:
	$(MAKE) -C src all CC=$(CC) AS=$(AS) SIZE=$(SIZE) BUILD_DIR=$(BUILD_DIR)

clean:
	$(MAKE) -C src clean BUILD_DIR=$(BUILD_DIR)
