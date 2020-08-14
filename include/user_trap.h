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
#ifndef _USER_EXCPT_H
#define _USER_EXCPT_H
#include "pcb.h"
#include "types.h"

/**
 * Delegate an exception to pcb, a user-mode process.
 * mcause and mtval holds the exception type and auxiliary information.
 */
pcb_t *handle_user_excpt(pcb_t *pcb, uintptr_t mcause, uintptr_t mtval);

/**
 * Delegate an interrupt to pcb, a user-mode process.
 * mcause holds the interrupt type.
 */
pcb_t *handle_user_intrp(pcb_t *pcb, uintptr_t mcause);

#endif /* _USER_EXCPT_H */
