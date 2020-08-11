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

export BUILD_DIR ?= $(CURDIR)/build-konglig
export CC = riscv64-unknown-elf-gcc
export SIZE = riscv64-unknown-elf-size

.PHONY: konglig
konglig:
	$(MAKE) -C konglig all 

.PHONY: clean 
clean:
	$(MAKE) -C konglig clean 
