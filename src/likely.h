/**
* @file likely.h
*
* @brief Likely/unlikley macros
*
* Likely/unlikely macros
*
* SPDX-FileCopyrightText: 2008-2021 D. Blackman and S. Vigna <vigna@acm.org>
* SPDX-License-Identifier: CC0-1.0
* SPDX-FileCopyrightText: 2008-2023 HPDCS Group <rootsim@googlegroups.com>
* SPDX-License-Identifier: GPL-3.0-only
*/
#pragma once

/// Optimize the branch as likely taken
#define likely(exp) __builtin_expect(!!(exp), 1)
/// Optimize the branch as likely not taken
#define unlikely(exp) __builtin_expect((exp), 0)
