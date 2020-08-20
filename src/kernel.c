#include "kernel.h"
#include "csr.h"
kernel_t kernel;

pcb_t *load_pcb(pcb_t *pcb) {
    CSRW(CSR_PMPCFG0, pcb->pmpcfg0);
    CSRW(CSR_PMPADDR0, pcb->pmpaddr[0]);
    CSRW(CSR_PMPADDR1, pcb->pmpaddr[1]);
    CSRW(CSR_PMPADDR2, pcb->pmpaddr[2]);
    CSRW(CSR_PMPADDR3, pcb->pmpaddr[3]);
    CSRW(CSR_PMPADDR4, pcb->pmpaddr[4]);
    CSRW(CSR_PMPADDR5, pcb->pmpaddr[5]);
    CSRW(CSR_PMPADDR6, pcb->pmpaddr[6]);
    CSRW(CSR_PMPADDR7, pcb->pmpaddr[7]);
}
