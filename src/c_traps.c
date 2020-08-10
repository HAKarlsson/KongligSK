#include "traps.h"
#include "util.h"

pcb_t* handle_excpt(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) {
    return pcb;
}
pcb_t* handle_intrp(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval) {
    return pcb;
}
