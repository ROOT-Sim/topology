/**
 * @file test/tests/lib/topology.c
 *
 * @brief Test: topology library
 *
 * SPDX-FileCopyrightText: 2008-2022 HPDCS Group <rootsim@googlegroups.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#include <test.h>
#include <ROOT-Sim/topology.h>

const enum topology_geometry LAST_TOPOLOGY_WITH_TWO_PARAMETERS = TOPOLOGY_TORUS;
const enum topology_geometry LAST_TOPOLOGY_VALID_VALUE = TOPOLOGY_GRAPH;
const enum topology_direction LAST_DIRECTION_VALID_VALUE = DIRECTION_SE;

// from random.c
extern struct {
	uint64_t state[4];
} ctx;


static int test_init_fini(_unused void *_)
{
	struct topology *topology;
	unsigned par1, par2; // Testing a variadic function, these are the two parameters

	for(enum topology_geometry i = 1; i <= LAST_TOPOLOGY_WITH_TWO_PARAMETERS; i++) {
		test_assert(InitializeTopology(i, 0, 0) == NULL);
		test_assert(InitializeTopology(i, 1, 0) == NULL);
		test_assert(InitializeTopology(i, 0, 1) == NULL);

		par1 = test_random_range(100) + 1;
		par2 = test_random_range(100) + 1;
		topology = InitializeTopology(i, par1, par2);
		test_assert(CountRegions(topology) == par1 * par2);
		test_assert(GetReceiver(par1 * par2 + 1, topology, DIRECTION_E) == INVALID_DIRECTION);
		test_assert(AddTopologyLink(topology, par1, par2, test_random_double()) == false);
		ReleaseTopology(topology);
	}

	for(enum topology_geometry i = LAST_TOPOLOGY_WITH_TWO_PARAMETERS + 1; i <= LAST_TOPOLOGY_VALID_VALUE; i++) {
		test_assert(InitializeTopology(i, 0) == NULL);

		par1 = test_random_range(100) + 1;
		topology = InitializeTopology(i, par1);
		test_assert(CountRegions(topology) == par1);
		test_assert(GetReceiver(par1 + 1, topology, DIRECTION_E) == INVALID_DIRECTION);
		ReleaseTopology(topology);
	}

	// Test if the variadic function detects a wrong number of parameters
	test_assert(InitializeTopology(TOPOLOGY_HEXAGON, 1) == NULL);
	test_assert(InitializeTopology(TOPOLOGY_HEXAGON, 1, 1, 1) == NULL);
	test_assert(InitializeTopology(TOPOLOGY_HEXAGON, 1, 1, 1, 1) == NULL);
	test_assert(InitializeTopology(TOPOLOGY_GRAPH, 1, 1) == NULL);
	test_assert(InitializeTopology(TOPOLOGY_GRAPH, 1, 1, 1) == NULL);
	test_assert(InitializeTopology(TOPOLOGY_GRAPH, 1, 1, 1, 1) == NULL);

	// Test what happens if wrong geometry is passed to InitializeTopology()
	test_assert(InitializeTopology(10 * TOPOLOGY_GRAPH, 1) == NULL);

	return 0;
}

int test_rng_is_initialized(_unused void *_)
{
	test_assert(ctx.state[0] != 0);
	test_assert(ctx.state[1] != 0);
	test_assert(ctx.state[2] != 0);
	test_assert(ctx.state[3] != 0);

	return 0;
}

int main(void)
{
	test("RNG is initialized", test_rng_is_initialized, NULL);
	test("Topology initialization and release", test_init_fini, NULL);
}
