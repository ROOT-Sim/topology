/**
 * @file random.h
 *
 * @brief topology RNG functions
 *
 * Topology RNG functions.
 *
 * SPDX-FileCopyrightText: 2008-2023 HPDCS Group <rootsim@googlegroups.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#pragma once

#include <stdint.h>

extern double topology_random(void);
extern int topology_randomrange(int min, int max);
