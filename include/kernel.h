#ifndef _KERNEL_H
#define _KERNEL_H
#include "config.h"
#include "pcb.h"

typedef struct kernel {
    pcb_t processes[NUM_OF_PROCESSES];
} kernel_t;

kernel_t kernel;

#endif /* _KERNEL_H */
