/**
 * @file test/tests/lib/topology.c
 *
 * @brief Test: topology library
 *
 * SPDX-FileCopyrightText: 2008-2025 HPDCS Group <rootsim@googlegroups.com>
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
	test_assert(GetReceiver(topology, 0, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NW) == INVALID_DIRECTION);

	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 1; j < 5; j++) // 5 is the number of regions in this test
			assert(GetReceiver(topology, j, DIRECTION_RANDOM) == 0);
		assert(GetReceiver(topology, 0, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Check directions count
	test_assert(CountDirections(topology, 0) > 1);
	test_assert(CountDirections(topology, 0) < CountRegions(topology));
	test_assert(CountDirections(topology, 1) == 1);
	test_assert(CountDirections(topology, 2) == 1);
	test_assert(CountDirections(topology, 3) == 1);
	test_assert(CountDirections(topology, 4) == 1);

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 0, 2) == true);
	test_assert(IsNeighbor(topology, 0, 3) == true);
	test_assert(IsNeighbor(topology, 0, 4) == true);
	test_assert(IsNeighbor(topology, 1, 0) == true);
	test_assert(IsNeighbor(topology, 2, 0) == true);
	test_assert(IsNeighbor(topology, 3, 0) == true);
	test_assert(IsNeighbor(topology, 4, 0) == true);
	test_assert(IsNeighbor(topology, 1, 2) == false);
	test_assert(IsNeighbor(topology, 2, 1) == false);
	test_assert(IsNeighbor(topology, 1, 3) == false);
	test_assert(IsNeighbor(topology, 3, 1) == false);
	test_assert(IsNeighbor(topology, 2, 4) == false);
	test_assert(IsNeighbor(topology, 4, 2) == false);

	ReleaseTopology(topology);

	return 0;
}

static int test_mesh(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_FCMESH, 5);

	// Sanity check
	test_assert(GetReceiver(topology, 0, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NW) == INVALID_DIRECTION);

	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 1; j < 5; j++) // 5 is the number of regions in this test
			test_assert(GetReceiver(topology, 0, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Check directions count
	test_assert(CountDirections(topology, 0) == CountRegions(topology) - 1);
	test_assert(CountDirections(topology, 1) == CountRegions(topology) - 1);
	test_assert(CountDirections(topology, 2) == CountRegions(topology) - 1);
	test_assert(CountDirections(topology, 3) == CountRegions(topology) - 1);
	test_assert(CountDirections(topology, 4) == CountRegions(topology) - 1);

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 0, 2) == true);
	test_assert(IsNeighbor(topology, 0, 3) == true);
	test_assert(IsNeighbor(topology, 0, 4) == true);
	test_assert(IsNeighbor(topology, 1, 0) == true);
	test_assert(IsNeighbor(topology, 2, 0) == true);
	test_assert(IsNeighbor(topology, 3, 0) == true);
	test_assert(IsNeighbor(topology, 4, 0) == true);
	test_assert(IsNeighbor(topology, 1, 2) == true);
	test_assert(IsNeighbor(topology, 2, 1) == true);
	test_assert(IsNeighbor(topology, 1, 3) == true);
	test_assert(IsNeighbor(topology, 3, 1) == true);
	test_assert(IsNeighbor(topology, 2, 4) == true);
	test_assert(IsNeighbor(topology, 4, 2) == true);

	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Star topology", test_star, NULL);
	test("Fully Connected Mesh topology", test_mesh, NULL);
}
