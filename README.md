# KongligSK
Separation kernel for RISC-V targeting secure embedded processors (M+U-mode and PMP). This is a playground for features, designs, and build system that may be included in [OpenMZ](https://github.com/castor-software/openmz). 

*Projected completion date 2025.*

## Kernel goals
- Formal verification - A separation kernel should be completely verified.
- Security - A separation kernel secures processes with spatial and temporal isolation.
- Performance - Fast context switches and IPC calls are essential for a separation kernel.
- Size - A small footprint is essential for both performance and embedded systems.
- Extensible - RISC-V has a lot of extensions (official and custom), so the kernel should be comfortably extensible.
- Real-time properties - RT properties makes the kernel suitable for some RT applications.

## API
WIP.

## Authors
- [Henrik Karlsson](https://github.com/HAKarlsson)

## Inspiration
- [seL4](https://sel4.systems/)
- [CertiKOS](http://flint.cs.yale.edu/certikos/)
