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

int test_hexagon(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_HEXAGON, 5, 4);

	// Test odd row
	test_assert(GetReceiver(5, topology, DIRECTION_W) == 4);
	test_assert(GetReceiver(5, topology, DIRECTION_E) == 6);
	test_assert(GetReceiver(5, topology, DIRECTION_NE) == 2);
	test_assert(GetReceiver(5, topology, DIRECTION_NW) == 1);
	test_assert(GetReceiver(5, topology, DIRECTION_SE) == 10);
	test_assert(GetReceiver(5, topology, DIRECTION_SW) == 9);

	// Test even row
	test_assert(GetReceiver(10, topology, DIRECTION_W) == 9);
	test_assert(GetReceiver(10, topology, DIRECTION_E) == 11);
	test_assert(GetReceiver(10, topology, DIRECTION_NE) == 6);
	test_assert(GetReceiver(10, topology, DIRECTION_NW) == 5);
	test_assert(GetReceiver(10, topology, DIRECTION_SE) == 14);
	test_assert(GetReceiver(10, topology, DIRECTION_SW) == 13);

	// Test boundaries
	test_assert(GetReceiver(0, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(1, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(1, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(2, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(2, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(3, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(3, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(3, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(7, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(7, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(7, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(11, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(15, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(15, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(15, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(19, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(19, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(19, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(18, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(18, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(17, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(17, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(16, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(16, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(16, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(16, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(12, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(8, topology, DIRECTION_SW) == INVALID_DIRECTION);
	test_assert(GetReceiver(8, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(8, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(4, topology, DIRECTION_W) == INVALID_DIRECTION);

	// Sanity checks
	test_assert(GetReceiver(5, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(5, topology, DIRECTION_S) == INVALID_DIRECTION);

	// Test neighbors count
	test_assert(CountDirections(0, topology) == 2);
	test_assert(CountDirections(1, topology) == 4);
	test_assert(CountDirections(2, topology) == 4);
	test_assert(CountDirections(3, topology) == 3);
	test_assert(CountDirections(4, topology) == 5);
	test_assert(CountDirections(7, topology) == 3);
	test_assert(CountDirections(8, topology) == 3);
	test_assert(CountDirections(11, topology) == 5);
	test_assert(CountDirections(12, topology) == 5);
	test_assert(CountDirections(15, topology) == 3);
	test_assert(CountDirections(16, topology) == 2);
	test_assert(CountDirections(17, topology) == 4);
	test_assert(CountDirections(18, topology) == 4);
	test_assert(CountDirections(19, topology) == 3);
	test_assert(CountDirections(5, topology) == 6);
	test_assert(CountDirections(10, topology) == 6);

	// Test random-bak receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 20; j++) // 20 is the number of regions in this test
			test_assert(GetReceiver(j, topology, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(0, 1, topology) == true);
	test_assert(IsNeighbor(0, 4, topology) == true);
	test_assert(IsNeighbor(5, 10, topology) == true);
	test_assert(IsNeighbor(17, 8, topology) == false);
	test_assert(IsNeighbor(7, 4, topology) == false);
	test_assert(IsNeighbor(3, 1, topology) == false);

	ReleaseTopology(topology);

	return 0;
}

int test_square(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_SQUARE, 3, 4);

	// Test all directions
	test_assert(GetReceiver(0, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_S) == 4);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_E) == 1);
	test_assert(GetReceiver(1, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(1, topology, DIRECTION_S) == 5);
	test_assert(GetReceiver(1, topology, DIRECTION_W) == 0);
	test_assert(GetReceiver(1, topology, DIRECTION_E) == 2);
	test_assert(GetReceiver(2, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(2, topology, DIRECTION_S) == 6);
	test_assert(GetReceiver(2, topology, DIRECTION_W) == 1);
	test_assert(GetReceiver(2, topology, DIRECTION_E) == 3);
	test_assert(GetReceiver(3, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(3, topology, DIRECTION_S) == 7);
	test_assert(GetReceiver(3, topology, DIRECTION_W) == 2);
	test_assert(GetReceiver(3, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(4, topology, DIRECTION_N) == 0);
	test_assert(GetReceiver(4, topology, DIRECTION_S) == 8);
	test_assert(GetReceiver(4, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(4, topology, DIRECTION_E) == 5);
	test_assert(GetReceiver(5, topology, DIRECTION_N) == 1);
	test_assert(GetReceiver(5, topology, DIRECTION_S) == 9);
	test_assert(GetReceiver(5, topology, DIRECTION_W) == 4);
	test_assert(GetReceiver(5, topology, DIRECTION_E) == 6);
	test_assert(GetReceiver(6, topology, DIRECTION_N) == 2);
	test_assert(GetReceiver(6, topology, DIRECTION_S) == 10);
	test_assert(GetReceiver(6, topology, DIRECTION_W) == 5);
	test_assert(GetReceiver(6, topology, DIRECTION_E) == 7);
	test_assert(GetReceiver(7, topology, DIRECTION_N) == 3);
	test_assert(GetReceiver(7, topology, DIRECTION_S) == 11);
	test_assert(GetReceiver(7, topology, DIRECTION_W) == 6);
	test_assert(GetReceiver(7, topology, DIRECTION_E) == INVALID_DIRECTION);
	test_assert(GetReceiver(8, topology, DIRECTION_N) == 4);
	test_assert(GetReceiver(8, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(8, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(8, topology, DIRECTION_E) == 9);
	test_assert(GetReceiver(9, topology, DIRECTION_N) == 5);
	test_assert(GetReceiver(9, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(9, topology, DIRECTION_W) == 8);
	test_assert(GetReceiver(9, topology, DIRECTION_E) == 10);
	test_assert(GetReceiver(10, topology, DIRECTION_N) == 6);
	test_assert(GetReceiver(10, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(10, topology, DIRECTION_W) == 9);
	test_assert(GetReceiver(10, topology, DIRECTION_E) == 11);
	test_assert(GetReceiver(11, topology, DIRECTION_N) == 7);
	test_assert(GetReceiver(11, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(11, topology, DIRECTION_W) == 10);
	test_assert(GetReceiver(11, topology, DIRECTION_E) == INVALID_DIRECTION);

	// Test neighbors count
	test_assert(CountDirections(0, topology) == 2);
	test_assert(CountDirections(1, topology) == 3);
	test_assert(CountDirections(2, topology) == 3);
	test_assert(CountDirections(3, topology) == 2);
	test_assert(CountDirections(4, topology) == 3);
	test_assert(CountDirections(5, topology) == 4);
	test_assert(CountDirections(6, topology) == 4);
	test_assert(CountDirections(7, topology) == 3);
	test_assert(CountDirections(8, topology) == 2);
	test_assert(CountDirections(9, topology) == 3);
	test_assert(CountDirections(10, topology) == 3);
	test_assert(CountDirections(11, topology) == 2);

	// Sanity check
	test_assert(GetReceiver(5, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(5, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(5, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(5, topology, DIRECTION_SW) == INVALID_DIRECTION);

	// Test random-bak receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 12; j++) // 12 is the number of regions in this test
			test_assert(GetReceiver(j, topology, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(0, 1, topology) == true);
	test_assert(IsNeighbor(0, 4, topology) == true);
	test_assert(IsNeighbor(5, 10, topology) == false);
	test_assert(IsNeighbor(11, 8, topology) == false);
	test_assert(IsNeighbor(7, 4, topology) == false);
	test_assert(IsNeighbor(3, 1, topology) == false);

	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Hexagon topology", test_hexagon, NULL);
	test("Square topology", test_square, NULL);
}
