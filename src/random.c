#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include <likely.h>
#include <random.h>
#include <xxtea.h>

struct {
	uint64_t state[4];
} ctx;

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
__attribute__((section(".init_array"))) __typeof__(init) *init_rstopology = init;

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
