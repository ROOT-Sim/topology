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

#define RANDOM_TRIALS 100000

int test_ring(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_RING, 5);

	// Sanity check
	test_assert(GetReceiver(0, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SW) == INVALID_DIRECTION);

	// Check valid directions
	test_assert(GetReceiver(0, topology, DIRECTION_E) == 1);
	test_assert(GetReceiver(1, topology, DIRECTION_E) == 2);
	test_assert(GetReceiver(2, topology, DIRECTION_E) == 3);
	test_assert(GetReceiver(3, topology, DIRECTION_E) == 4);
	test_assert(GetReceiver(4, topology, DIRECTION_E) == 0);

	// Test neighbors count
	test_assert(CountDirections(0, topology) == 1);
	test_assert(CountDirections(1, topology) == 1);
	test_assert(CountDirections(2, topology) == 1);
	test_assert(CountDirections(3, topology) == 1);
	test_assert(CountDirections(4, topology) == 1);

	// Test random-bak receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 5; j++) // 5 is the number of regions in this test
			test_assert(GetReceiver(j, topology, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(0, 1, topology) == true);
	test_assert(IsNeighbor(1, 2, topology) == true);
	test_assert(IsNeighbor(2, 4, topology) == false);
	test_assert(IsNeighbor(1, 0, topology) == false);
	test_assert(IsNeighbor(2, 1, topology) == false);
	test_assert(IsNeighbor(4, 2, topology) == false);

	ReleaseTopology(topology);

	return 0;
}

int test_bidring(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_BIDRING, 5);

	// Sanity check
	test_assert(GetReceiver(0, topology, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(0, topology, DIRECTION_SW) == INVALID_DIRECTION);

	// Check valid directions
	test_assert(GetReceiver(0, topology, DIRECTION_E) == 1);
	test_assert(GetReceiver(1, topology, DIRECTION_E) == 2);
	test_assert(GetReceiver(2, topology, DIRECTION_E) == 3);
	test_assert(GetReceiver(3, topology, DIRECTION_E) == 4);
	test_assert(GetReceiver(4, topology, DIRECTION_E) == 0);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == 4);
	test_assert(GetReceiver(1, topology, DIRECTION_W) == 0);
	test_assert(GetReceiver(2, topology, DIRECTION_W) == 1);
	test_assert(GetReceiver(3, topology, DIRECTION_W) == 2);
	test_assert(GetReceiver(4, topology, DIRECTION_W) == 3);

	// Test neighbors count
	test_assert(CountDirections(0, topology) == 2);
	test_assert(CountDirections(1, topology) == 2);
	test_assert(CountDirections(2, topology) == 2);
	test_assert(CountDirections(3, topology) == 2);
	test_assert(CountDirections(4, topology) == 2);

	// Test random-bak receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 5; j++) // 5 is the number of regions in this test
			test_assert(GetReceiver(j, topology, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(0, 1, topology) == true);
	test_assert(IsNeighbor(1, 2, topology) == true);
	test_assert(IsNeighbor(2, 4, topology) == false);
	test_assert(IsNeighbor(1, 0, topology) == true);
	test_assert(IsNeighbor(2, 1, topology) == true);
	test_assert(IsNeighbor(4, 2, topology) == false);

	ReleaseTopology(topology);

	return 0;
}

int test_torus(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_TORUS, 3, 4);

	// Test all directions
	test_assert(GetReceiver(0, topology, DIRECTION_N) == 8);
	test_assert(GetReceiver(0, topology, DIRECTION_S) == 4);
	test_assert(GetReceiver(0, topology, DIRECTION_W) == 3);
	test_assert(GetReceiver(0, topology, DIRECTION_E) == 1);
	test_assert(GetReceiver(1, topology, DIRECTION_N) == 9);
	test_assert(GetReceiver(1, topology, DIRECTION_S) == 5);
	test_assert(GetReceiver(1, topology, DIRECTION_W) == 0);
	test_assert(GetReceiver(1, topology, DIRECTION_E) == 2);
	test_assert(GetReceiver(2, topology, DIRECTION_N) == 10);
	test_assert(GetReceiver(2, topology, DIRECTION_S) == 6);
	test_assert(GetReceiver(2, topology, DIRECTION_W) == 1);
	test_assert(GetReceiver(2, topology, DIRECTION_E) == 3);
	test_assert(GetReceiver(3, topology, DIRECTION_N) == 11);
	test_assert(GetReceiver(3, topology, DIRECTION_S) == 7);
	test_assert(GetReceiver(3, topology, DIRECTION_W) == 2);
	test_assert(GetReceiver(3, topology, DIRECTION_E) == 0);
	test_assert(GetReceiver(4, topology, DIRECTION_N) == 0);
	test_assert(GetReceiver(4, topology, DIRECTION_S) == 8);
	test_assert(GetReceiver(4, topology, DIRECTION_W) == 7);
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
	test_assert(GetReceiver(7, topology, DIRECTION_E) == 4);
	test_assert(GetReceiver(8, topology, DIRECTION_N) == 4);
	test_assert(GetReceiver(8, topology, DIRECTION_S) == 0);
	test_assert(GetReceiver(8, topology, DIRECTION_W) == 11);
	test_assert(GetReceiver(8, topology, DIRECTION_E) == 9);
	test_assert(GetReceiver(9, topology, DIRECTION_N) == 5);
	test_assert(GetReceiver(9, topology, DIRECTION_S) == 1);
	test_assert(GetReceiver(9, topology, DIRECTION_W) == 8);
	test_assert(GetReceiver(9, topology, DIRECTION_E) == 10);
	test_assert(GetReceiver(10, topology, DIRECTION_N) == 6);
	test_assert(GetReceiver(10, topology, DIRECTION_S) == 2);
	test_assert(GetReceiver(10, topology, DIRECTION_W) == 9);
	test_assert(GetReceiver(10, topology, DIRECTION_E) == 11);
	test_assert(GetReceiver(11, topology, DIRECTION_N) == 7);
	test_assert(GetReceiver(11, topology, DIRECTION_S) == 3);
	test_assert(GetReceiver(11, topology, DIRECTION_W) == 10);
	test_assert(GetReceiver(11, topology, DIRECTION_E) == 8);

	// Test neighbors count
	test_assert(CountDirections(0, topology) == 4);
	test_assert(CountDirections(1, topology) == 4);
	test_assert(CountDirections(2, topology) == 4);
	test_assert(CountDirections(3, topology) == 4);
	test_assert(CountDirections(4, topology) == 4);
	test_assert(CountDirections(5, topology) == 4);
	test_assert(CountDirections(6, topology) == 4);
	test_assert(CountDirections(7, topology) == 4);
	test_assert(CountDirections(8, topology) == 4);
	test_assert(CountDirections(9, topology) == 4);
	test_assert(CountDirections(10, topology) == 4);
	test_assert(CountDirections(11, topology) == 4);

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
	test_assert(IsNeighbor(11, 8, topology) == true);
	test_assert(IsNeighbor(3, 11, topology) == true);
	test_assert(IsNeighbor(3, 1, topology) == false);

	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Ring topology", test_ring, NULL);
	test("BidRing topology", test_bidring, NULL);
	test("Torus topology", test_torus, NULL);
}
