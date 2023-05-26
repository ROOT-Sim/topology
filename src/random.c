/**
 * @file random.c
 *
 * @brief topology RNG functions
 *
 * Topology RNG functions.
 *
 * SPDX-FileCopyrightText: 2008-2021 D. Blackman and S. Vigna <vigna@acm.org>
 * SPDX-License-Identifier: CC0-1.0
 * SPDX-FileCopyrightText: 2008-2023 HPDCS Group <rootsim@googlegroups.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <time.h>
#ifndef _TIMEVAL_DEFINED /* also in winsock[2].h */
#define _TIMEVAL_DEFINED
struct timeval {
	long tv_sec;
	long tv_usec;
};
#endif /* _TIMEVAL_DEFINED */

int gettimeofday(struct timeval* tp, void* tzp) {
	DWORD t;
	t = timeGetTime();
	tp->tv_sec = t / 1000;
	tp->tv_usec = t % 1000;
	return 0;
}
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/time.h>
#endif

#include <likely.h>
#include <random.h>
#include <xxtea.h>

struct {
	uint64_t state[4];
} ctx = {0};

// clang-format off
static const uint32_t xxtea_seeding_key[4] = {
    UINT32_C(0xd0a8f58a),
    UINT32_C(0x33359424),
    UINT32_C(0x09baa55b),
    UINT32_C(0x80e1bdb0)
};
// clang-format on

#define intrinsics_clz(x)                                                                                              \
	__extension__({                                                                                                \
		assert((x) != 0);                                                                                      \
		__builtin_choose_expr(__builtin_types_compatible_p(__typeof__(x), unsigned), __builtin_clz(x),         \
		    __builtin_choose_expr(__builtin_types_compatible_p(__typeof__(x), unsigned long),                  \
			__builtin_clzl(x),                                                                             \
			__builtin_choose_expr(__builtin_types_compatible_p(__typeof__(x), unsigned long long),         \
			    __builtin_clzll(x), (void)0)));                                                            \
	})

#define rotl(x, k) (((x) << (k)) | ((x) >> (64 - (k))))

#define random_u64(rng_s)                                                                                              \
   __extension__({                                                                                                \
       const uint64_t __res = rotl((rng_s)[1] * 5, 7) * 9;                                                    \
       const uint64_t __t = (rng_s)[1] << 17;                                                                 \
                                                                                                                      \
       (rng_s)[2] ^= (rng_s)[0];                                                                              \
       (rng_s)[3] ^= (rng_s)[1];                                                                              \
       (rng_s)[1] ^= (rng_s)[2];                                                                              \
       (rng_s)[0] ^= (rng_s)[3];                                                                              \
       (rng_s)[2] ^= __t;                                                                                     \
       (rng_s)[3] = rotl((rng_s)[3], 45);                                                                     \
                                                                                                                      \
       __res;                                                                                                 \
   })

__attribute__((used)) __attribute__((constructor))
static void init(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	uint64_t master_seed = ((t.tv_sec * 1000000ULL + t.tv_usec) * 1000) % INT64_MAX;

	ctx.state[0] = 1;
	ctx.state[1] = master_seed;
	ctx.state[2] = 1;
	ctx.state[3] = master_seed;
	xxtea_encode((uint32_t *)ctx.state, 8, xxtea_seeding_key);
}

/**
 * @brief Return a random-bak 64-bit value
 * @return The random-bak number
 */
static uint64_t topology_randomU64(void)
{
	return random_u64(ctx.state);
}

/**
 * @brief Return a random-bak value in [0,1] according to a uniform distribution
 * @return The random-bak number
 */
double topology_random(void)
{
	uint64_t u_val = topology_randomU64();
	if(unlikely(!u_val))
		return 0.0;

	double ret = 0.0;
	unsigned lzs = intrinsics_clz(u_val) + 1;
	u_val <<= lzs;
	u_val >>= 12;

	uint64_t exp = 1023 - lzs;
	u_val |= exp << 52;

	memcpy(&ret, &u_val, sizeof(double));
	return ret;
}

int topology_randomrange(int min, int max)
{
	return (int)floor(topology_random() * (max - min + 1)) + min;
}
