/* 
 * This file is part of KongligSK.
 * Copyright (c) 2020 Henrik Karlsson <henrik10@kth.se>.
 * 
 * KongligSK is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * KongligSK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with KongligSK.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _TRAPS_H
#define _TRAPS_H
#include "pcb.h"
#include "types.h"
#include "util.h"

extern void trap_entry(void) NO_RETURN;
extern void trap_exit(pcb_t *pcb) NO_RETURN;
pcb_t* handle_excpt(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval); 
pcb_t* handle_intrp(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval);

#endif /* _TRAPS_H */
