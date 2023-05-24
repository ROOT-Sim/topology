/**
* @file xoroshiro.h
*
* @brief Xoroshiro RNG support functions
*
* Xoroshiro RNG support functions.
*
* SPDX-FileCopyrightText: 2008-2021 D. Blackman and S. Vigna <vigna@acm.org>
* SPDX-License-Identifier: CC0-1.0
*/
#pragma once

#include <stdint.h>

extern double topology_random(void);
extern int topology_randomrange(int min, int max);
