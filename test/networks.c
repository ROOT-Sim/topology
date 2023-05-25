/**
 * @file test/tests/lib/topology.c
 *
 * @brief Test: topology library
 *
 * SPDX-FileCopyrightText: 2008-2022 HPDCS Group <rootsim@googlegroups.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#include <assert.h>
#include <limits.h>

#include <test.h>
#include <ROOT-Sim/topology.h>

#define RANDOM_TRIALS 100000

static int test_star(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_STAR, 5);

	// Sanity check
	test_assert(GetReceiver(0, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NW) == INVALID_DIRECTION);

	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 1; j < 5; j++) // 5 is the number of regions in this test
			assert(GetReceiver(j, topology, DIRECTION_RANDOM) == 0);
		assert(GetReceiver(0, topology, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Check directions count
	test_assert(CountDirections(0, topology) > 1);
	test_assert(CountDirections(0, topology) < CountRegions(topology));
	test_assert(CountDirections(1, topology) == 1);
	test_assert(CountDirections(2, topology) == 1);
	test_assert(CountDirections(3, topology) == 1);
	test_assert(CountDirections(4, topology) == 1);

	// Test neighbor check
	test_assert(IsNeighbor(0, 1, topology) == true);
	test_assert(IsNeighbor(0, 2, topology) == true);
	test_assert(IsNeighbor(0, 3, topology) == true);
	test_assert(IsNeighbor(0, 4, topology) == true);
	test_assert(IsNeighbor(1, 0, topology) == true);
	test_assert(IsNeighbor(2, 0, topology) == true);
	test_assert(IsNeighbor(3, 0, topology) == true);
	test_assert(IsNeighbor(4, 0, topology) == true);
	test_assert(IsNeighbor(1, 2, topology) == false);
	test_assert(IsNeighbor(2, 1, topology) == false);
	test_assert(IsNeighbor(1, 3, topology) == false);
	test_assert(IsNeighbor(3, 1, topology) == false);
	test_assert(IsNeighbor(2, 4, topology) == false);
	test_assert(IsNeighbor(4, 2, topology) == false);

	ReleaseTopology(topology);

	return 0;
}

static int test_mesh(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_FCMESH, 5);

	// Sanity check
	test_assert(GetReceiver(0, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NW) == INVALID_DIRECTION);

	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 1; j < 5; j++) // 5 is the number of regions in this test
			test_assert(GetReceiver(0, topology, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Check directions count
	test_assert(CountDirections(0, topology) == CountRegions(topology) - 1);
	test_assert(CountDirections(1, topology) == CountRegions(topology) - 1);
	test_assert(CountDirections(2, topology) == CountRegions(topology) - 1);
	test_assert(CountDirections(3, topology) == CountRegions(topology) - 1);
	test_assert(CountDirections(4, topology) == CountRegions(topology) - 1);

	// Test neighbor check
	test_assert(IsNeighbor(0, 1, topology) == true);
	test_assert(IsNeighbor(0, 2, topology) == true);
	test_assert(IsNeighbor(0, 3, topology) == true);
	test_assert(IsNeighbor(0, 4, topology) == true);
	test_assert(IsNeighbor(1, 0, topology) == true);
	test_assert(IsNeighbor(2, 0, topology) == true);
	test_assert(IsNeighbor(3, 0, topology) == true);
	test_assert(IsNeighbor(4, 0, topology) == true);
	test_assert(IsNeighbor(1, 2, topology) == true);
	test_assert(IsNeighbor(2, 1, topology) == true);
	test_assert(IsNeighbor(1, 3, topology) == true);
	test_assert(IsNeighbor(3, 1, topology) == true);
	test_assert(IsNeighbor(2, 4, topology) == true);
	test_assert(IsNeighbor(4, 2, topology) == true);

	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Star topology", test_star, NULL);
	test("Fully Connected Mesh topology", test_mesh, NULL);
}
