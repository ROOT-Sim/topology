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

int test_hexagon(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_HEXAGON, 5, 4);

	// Test odd row
	test_assert(GetReceiver(topology, 5, DIRECTION_W) == 4);
	test_assert(GetReceiver(topology, 5, DIRECTION_E) == 6);
	test_assert(GetReceiver(topology, 5, DIRECTION_NE) == 2);
	test_assert(GetReceiver(topology, 5, DIRECTION_NW) == 1);
	test_assert(GetReceiver(topology, 5, DIRECTION_SE) == 10);
	test_assert(GetReceiver(topology, 5, DIRECTION_SW) == 9);

	// Test even row
	test_assert(GetReceiver(topology, 10, DIRECTION_W) == 9);
	test_assert(GetReceiver(topology, 10, DIRECTION_E) == 11);
	test_assert(GetReceiver(topology, 10, DIRECTION_NE) == 6);
	test_assert(GetReceiver(topology, 10, DIRECTION_NW) == 5);
	test_assert(GetReceiver(topology, 10, DIRECTION_SE) == 14);
	test_assert(GetReceiver(topology, 10, DIRECTION_SW) == 13);

	// Test boundaries
	test_assert(GetReceiver(topology, 0, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 1, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 1, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 2, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 2, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 3, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 3, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 3, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 7, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 7, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 7, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 11, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 15, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 15, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 15, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 19, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 19, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 19, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 18, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 18, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 17, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 17, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 16, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 16, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 16, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 16, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 12, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 8, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 8, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 8, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 4, DIRECTION_W) == INVALID_DIRECTION);

	// Sanity checks
	test_assert(GetReceiver(topology, 5, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_S) == INVALID_DIRECTION);

	// Test neighbors count
	test_assert(CountDirections(topology, 0) == 2);
	test_assert(CountDirections(topology, 1) == 4);
	test_assert(CountDirections(topology, 2) == 4);
	test_assert(CountDirections(topology, 3) == 3);
	test_assert(CountDirections(topology, 4) == 5);
	test_assert(CountDirections(topology, 5) == 6);
	test_assert(CountDirections(topology, 6) == 6);
	test_assert(CountDirections(topology, 7) == 3);
	test_assert(CountDirections(topology, 8) == 3);
	test_assert(CountDirections(topology, 9) == 6);
	test_assert(CountDirections(topology, 10) == 6);
	test_assert(CountDirections(topology, 11) == 5);
	test_assert(CountDirections(topology, 12) == 5);
	test_assert(CountDirections(topology, 15) == 3);
	test_assert(CountDirections(topology, 16) == 2);
	test_assert(CountDirections(topology, 17) == 4);
	test_assert(CountDirections(topology, 18) == 4);
	test_assert(CountDirections(topology, 19) == 3);

	// Test GetAllReceivers
	lp_id_t receivers[CountDirections(topology, 4)];
	GetAllReceivers(topology, 4, receivers);
	test_assert(receivers[0] == 5);
	test_assert(receivers[1] == 1);
	test_assert(receivers[2] == 0);
	test_assert(receivers[3] == 9);
	test_assert(receivers[4] == 8);

	// Test random receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 20; j++) // 20 is the number of regions in this test
			test_assert(GetReceiver(topology, j, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 0, 4) == true);
	test_assert(IsNeighbor(topology, 5, 10) == true);
	test_assert(IsNeighbor(topology, 17, 8) == false);
	test_assert(IsNeighbor(topology, 7, 4) == false);
	test_assert(IsNeighbor(topology, 3, 1) == false);

	ReleaseTopology(topology);

	return 0;
}

int test_square(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_SQUARE, 3, 4);

	// Test all directions
	test_assert(GetReceiver(topology, 0, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_S) == 4);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_E) == 1);
	test_assert(GetReceiver(topology, 1, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 1, DIRECTION_S) == 5);
	test_assert(GetReceiver(topology, 1, DIRECTION_W) == 0);
	test_assert(GetReceiver(topology, 1, DIRECTION_E) == 2);
	test_assert(GetReceiver(topology, 2, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 2, DIRECTION_S) == 6);
	test_assert(GetReceiver(topology, 2, DIRECTION_W) == 1);
	test_assert(GetReceiver(topology, 2, DIRECTION_E) == 3);
	test_assert(GetReceiver(topology, 3, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 3, DIRECTION_S) == 7);
	test_assert(GetReceiver(topology, 3, DIRECTION_W) == 2);
	test_assert(GetReceiver(topology, 3, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 4, DIRECTION_N) == 0);
	test_assert(GetReceiver(topology, 4, DIRECTION_S) == 8);
	test_assert(GetReceiver(topology, 4, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 4, DIRECTION_E) == 5);
	test_assert(GetReceiver(topology, 5, DIRECTION_N) == 1);
	test_assert(GetReceiver(topology, 5, DIRECTION_S) == 9);
	test_assert(GetReceiver(topology, 5, DIRECTION_W) == 4);
	test_assert(GetReceiver(topology, 5, DIRECTION_E) == 6);
	test_assert(GetReceiver(topology, 6, DIRECTION_N) == 2);
	test_assert(GetReceiver(topology, 6, DIRECTION_S) == 10);
	test_assert(GetReceiver(topology, 6, DIRECTION_W) == 5);
	test_assert(GetReceiver(topology, 6, DIRECTION_E) == 7);
	test_assert(GetReceiver(topology, 7, DIRECTION_N) == 3);
	test_assert(GetReceiver(topology, 7, DIRECTION_S) == 11);
	test_assert(GetReceiver(topology, 7, DIRECTION_W) == 6);
	test_assert(GetReceiver(topology, 7, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 8, DIRECTION_N) == 4);
	test_assert(GetReceiver(topology, 8, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 8, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 8, DIRECTION_E) == 9);
	test_assert(GetReceiver(topology, 9, DIRECTION_N) == 5);
	test_assert(GetReceiver(topology, 9, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 9, DIRECTION_W) == 8);
	test_assert(GetReceiver(topology, 9, DIRECTION_E) == 10);
	test_assert(GetReceiver(topology, 10, DIRECTION_N) == 6);
	test_assert(GetReceiver(topology, 10, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 10, DIRECTION_W) == 9);
	test_assert(GetReceiver(topology, 10, DIRECTION_E) == 11);
	test_assert(GetReceiver(topology, 11, DIRECTION_N) == 7);
	test_assert(GetReceiver(topology, 11, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 11, DIRECTION_W) == 10);
	test_assert(GetReceiver(topology, 11, DIRECTION_E) == INVALID_DIRECTION);

	// Test GetAllReceivers
	lp_id_t receivers[CountDirections(topology, 3)];
	GetAllReceivers(topology, 3, receivers);
	test_assert(receivers[0] == 2);
	test_assert(receivers[1] == 7);

	// Test neighbors count
	test_assert(CountDirections(topology, 0) == 2);
	test_assert(CountDirections(topology, 1) == 3);
	test_assert(CountDirections(topology, 2) == 3);
	test_assert(CountDirections(topology, 3) == 2);
	test_assert(CountDirections(topology, 4) == 3);
	test_assert(CountDirections(topology, 5) == 4);
	test_assert(CountDirections(topology, 6) == 4);
	test_assert(CountDirections(topology, 7) == 3);
	test_assert(CountDirections(topology, 8) == 2);
	test_assert(CountDirections(topology, 9) == 3);
	test_assert(CountDirections(topology, 10) == 3);
	test_assert(CountDirections(topology, 11) == 2);

	// Sanity check
	test_assert(GetReceiver(topology, 5, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_SW) == INVALID_DIRECTION);

	// Test random receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 12; j++) // 12 is the number of regions in this test
			test_assert(GetReceiver(topology, j, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 0, 4) == true);
	test_assert(IsNeighbor(topology, 5, 10) == false);
	test_assert(IsNeighbor(topology, 11, 8) == false);
	test_assert(IsNeighbor(topology, 7, 4) == false);
	test_assert(IsNeighbor(topology, 3, 1) == false);

	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Hexagon topology", test_hexagon, NULL);
	test("Square topology", test_square, NULL);
}
