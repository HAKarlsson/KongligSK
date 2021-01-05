// SPDX-License-Identifier: GPL-3.0-only
// Copyright 2020-2021, Henrik Karlsson
#include "boot.h"

#include "part.h"
#include "traps.h"

void init_kernel(void) {
	current_init(&parts[0]);
	trap_exit();
}
