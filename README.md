# KongligSK
KongligSK (~Royal Separation Kernel) is a separation kernel for RISC-V targeting secure embedded processors (M+U-mode and PMP). KongligSK is a research kernel for features, designs, and build system that may be included in [OpenMZ](https://github.com/castor-software/openmz). KongligSK is a part of a research project on provably secure at KTH Royal Institute of Technology ([KTH](https://www.kth.se/en)), Center for Cyber Defence and Information Security ([CDIS](https://www.kth.se/cdis)).

*Projected completion date 2025.*

## Kernel goals

- **Formal Verification.** A separation kernel should be completely verified. We consider two approaches to the verification.

    1. We formally verify the C code with respect to a formal model of the kernel and the RISC-V specification. This allows us to compile the kernel with formally verified compiler [CompCert](https://github.com/AbsInt/CompCert), and get a fully formally verified kernel.

    2. We formally verify the kernel binary using [HolBA](https://github.com/kth-step/HolBA), allowing us to use any compiler and thus get better optimization.

- **Security.** A separation kernel should secure processes with spatial and temporal isolation.

- **Performance.** Fast context switches and IPC calls are essential for a separation kernel.

- **Small footprint.** A small footprint is important for most embedded systems.

- **Extensible.** RISC-V has a lot of extensions (official and custom) and these extension can invalidate the kernel verification. We want to synthesize kernel code that extends the kernel functionality and verification.

- **Real-time properties.** Real-time properties makes the kernel suitable for some RT applications. Exact properties TBD.

## API
TBD.

## Guide
KongligSK requires
- `make` - for building the system (required) 
- `python3` - for making configuration file (required)
- `riscv64-unknown-elf-gcc` - compiling source files (required)
- `riscv64-unknown-elf-ld` - linking object files (required)
- `riscv64-unknown-elf-objdump` - examine binary files (recommended)
- `riscv64-unknown-elf-size` - examine binary size (optional) 
- `cloc` - count lines of code (optional)
- `clang-format` - format source and header files (optional)

### Ubuntu 20.04 install
```
sudo apt install make python3 gcc-riscv64-unknown-elf cloc clang-format
```

### Make targets
- `make all` - generate configuration, make binary files and disassembly files.
- `make clean` - delete binary, and generated configuration files
- `make config` - generate configuration file
- `make elf` - make binary files
- `make disassembly` or `make da` - make disassembly files (.da in build folder) 
- `make format` - format source and header files
- `make size` - display size of binary files in bytes
- `make cloc` - count lines of code

### Make options
To use one of the following options, do `make <OPTION1>=<value1> <OPTION2>=<value2> ..`, for example `make CONFIG_FILE=my_configuration.yaml`.
- `CONFIG` - configuration file, see example\_config.yaml. (default = example\_config.yaml)
- `LDS` - Path of linker script (default = example\_linker\_script.lds)
- `BUILD_DIR` -  target directory, all generated binary and disassembly files goes here (default = build)
- `RISCV_PREFIX` - Prefix of your RISC-V toolchain. (default = riscv64-unknown-elf-)
- `ELF` - Path of generated ELF file (default = BUILD\_DIR/konglig.elf

### Configuring the Kernel

TODO

## TODO

1. Determine the API of the kernel.

2. Benchmark the kernel using gcc and compcert on HiFive1 rev. B. This will determine whether we should formally verify the kernel source code or binary. If the gcc version gives us a kernel with considerably better performance, we will verify the kernel binary.

3. Write a pen and paper model and proof of the kernel.

4. Create a formal model of the kernel in [HOL](https://hol-theorem-prover.org/).

5. TBD.

## Related Projects 
- [seL4](https://sel4.systems/) - A verified and secure µ-kernel, suitable for more capable hardware.
- [eChronos](https://github.com/echronos/echronos) - a real-time operating systems.
- [CertiKOS](http://flint.cs.yale.edu/certikos/) - A verified, secure and modularized kernel for more capable hardware.
- [Keystone Enclave](https://github.com/keystone-enclave/keystone) - A lightweight TEE for RISC-V.
- [MultiZone Security](https://hex-five.com) - A lightweight TEE for RISC-V.
- [STH](https://bitbucket.org/sicssec/sth/src/master/) - SICS Thin Hypervisor, a research kernel part of the PROSPER project.

## Authors
- [Henrik Karlsson](https://github.com/HAKarlsson)

## Copyright
Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.

KongligSK is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KongligSK is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.
