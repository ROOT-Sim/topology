/**
 * @file test/tests/lib/topology.c
 *
 * @brief Test: topology library
 *
 * SPDX-FileCopyrightText: 2008-2025 HPDCS Group <rootsim@googlegroups.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#include <test.h>
#include <ROOT-Sim/topology.h>

#define RANDOM_TRIALS 100000

int test_ring(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_RING, 5);

	// Sanity check
	test_assert(GetReceiver(topology, 0, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SW) == INVALID_DIRECTION);

	// Check valid directions
	test_assert(GetReceiver(topology, 0, DIRECTION_E) == 1);
	test_assert(GetReceiver(topology, 1, DIRECTION_E) == 2);
	test_assert(GetReceiver(topology, 2, DIRECTION_E) == 3);
	test_assert(GetReceiver(topology, 3, DIRECTION_E) == 4);
	test_assert(GetReceiver(topology, 4, DIRECTION_E) == 0);

	// Test neighbors count
	test_assert(CountDirections(topology, 0) == 1);
	test_assert(CountDirections(topology, 1) == 1);
	test_assert(CountDirections(topology, 2) == 1);
	test_assert(CountDirections(topology, 3) == 1);
	test_assert(CountDirections(topology, 4) == 1);

	// Test GetAllReceivers
	lp_id_t receivers[CountDirections(topology, 3)];
	GetAllReceivers(topology, 3, receivers);
	test_assert(receivers[0] == 4);

	// Test random receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 5; j++) // 5 is the number of regions in this test
			test_assert(GetReceiver(topology, j, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 1, 2) == true);
	test_assert(IsNeighbor(topology, 2, 4) == false);
	test_assert(IsNeighbor(topology, 1, 0) == false);
	test_assert(IsNeighbor(topology, 2, 1) == false);
	test_assert(IsNeighbor(topology, 4, 2) == false);

	ReleaseTopology(topology);

	return 0;
}

int test_bidring(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_BIDRING, 5);

	// Sanity check
	test_assert(GetReceiver(topology, 0, DIRECTION_N) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_S) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 0, DIRECTION_SW) == INVALID_DIRECTION);

	// Check valid directions
	test_assert(GetReceiver(topology, 0, DIRECTION_E) == 1);
	test_assert(GetReceiver(topology, 1, DIRECTION_E) == 2);
	test_assert(GetReceiver(topology, 2, DIRECTION_E) == 3);
	test_assert(GetReceiver(topology, 3, DIRECTION_E) == 4);
	test_assert(GetReceiver(topology, 4, DIRECTION_E) == 0);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == 4);
	test_assert(GetReceiver(topology, 1, DIRECTION_W) == 0);
	test_assert(GetReceiver(topology, 2, DIRECTION_W) == 1);
	test_assert(GetReceiver(topology, 3, DIRECTION_W) == 2);
	test_assert(GetReceiver(topology, 4, DIRECTION_W) == 3);

	// Test neighbors count
	test_assert(CountDirections(topology, 0) == 2);
	test_assert(CountDirections(topology, 1) == 2);
	test_assert(CountDirections(topology, 2) == 2);
	test_assert(CountDirections(topology, 3) == 2);
	test_assert(CountDirections(topology, 4) == 2);

	// Test GetAllReceivers
	lp_id_t receivers[CountDirections(topology, 3)];
	GetAllReceivers(topology, 3, receivers);
	test_assert(receivers[0] == 4);
	test_assert(receivers[1] == 2);

	// Test random receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 5; j++) // 5 is the number of regions in this test
			test_assert(GetReceiver(topology, j, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 1, 2) == true);
	test_assert(IsNeighbor(topology, 2, 4) == false);
	test_assert(IsNeighbor(topology, 1, 0) == true);
	test_assert(IsNeighbor(topology, 2, 1) == true);
	test_assert(IsNeighbor(topology, 4, 2) == false);

	ReleaseTopology(topology);

	return 0;
}

int test_torus(_unused void *_)
{
	struct topology *topology = InitializeTopology(TOPOLOGY_TORUS, 3, 4);

	// Test all directions
	test_assert(GetReceiver(topology, 0, DIRECTION_N) == 8);
	test_assert(GetReceiver(topology, 0, DIRECTION_S) == 4);
	test_assert(GetReceiver(topology, 0, DIRECTION_W) == 3);
	test_assert(GetReceiver(topology, 0, DIRECTION_E) == 1);
	test_assert(GetReceiver(topology, 1, DIRECTION_N) == 9);
	test_assert(GetReceiver(topology, 1, DIRECTION_S) == 5);
	test_assert(GetReceiver(topology, 1, DIRECTION_W) == 0);
	test_assert(GetReceiver(topology, 1, DIRECTION_E) == 2);
	test_assert(GetReceiver(topology, 2, DIRECTION_N) == 10);
	test_assert(GetReceiver(topology, 2, DIRECTION_S) == 6);
	test_assert(GetReceiver(topology, 2, DIRECTION_W) == 1);
	test_assert(GetReceiver(topology, 2, DIRECTION_E) == 3);
	test_assert(GetReceiver(topology, 3, DIRECTION_N) == 11);
	test_assert(GetReceiver(topology, 3, DIRECTION_S) == 7);
	test_assert(GetReceiver(topology, 3, DIRECTION_W) == 2);
	test_assert(GetReceiver(topology, 3, DIRECTION_E) == 0);
	test_assert(GetReceiver(topology, 4, DIRECTION_N) == 0);
	test_assert(GetReceiver(topology, 4, DIRECTION_S) == 8);
	test_assert(GetReceiver(topology, 4, DIRECTION_W) == 7);
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
	test_assert(GetReceiver(topology, 7, DIRECTION_E) == 4);
	test_assert(GetReceiver(topology, 8, DIRECTION_N) == 4);
	test_assert(GetReceiver(topology, 8, DIRECTION_S) == 0);
	test_assert(GetReceiver(topology, 8, DIRECTION_W) == 11);
	test_assert(GetReceiver(topology, 8, DIRECTION_E) == 9);
	test_assert(GetReceiver(topology, 9, DIRECTION_N) == 5);
	test_assert(GetReceiver(topology, 9, DIRECTION_S) == 1);
	test_assert(GetReceiver(topology, 9, DIRECTION_W) == 8);
	test_assert(GetReceiver(topology, 9, DIRECTION_E) == 10);
	test_assert(GetReceiver(topology, 10, DIRECTION_N) == 6);
	test_assert(GetReceiver(topology, 10, DIRECTION_S) == 2);
	test_assert(GetReceiver(topology, 10, DIRECTION_W) == 9);
	test_assert(GetReceiver(topology, 10, DIRECTION_E) == 11);
	test_assert(GetReceiver(topology, 11, DIRECTION_N) == 7);
	test_assert(GetReceiver(topology, 11, DIRECTION_S) == 3);
	test_assert(GetReceiver(topology, 11, DIRECTION_W) == 10);
	test_assert(GetReceiver(topology, 11, DIRECTION_E) == 8);

	// Test neighbors count
	test_assert(CountDirections(topology, 0) == 4);
	test_assert(CountDirections(topology, 1) == 4);
	test_assert(CountDirections(topology, 2) == 4);
	test_assert(CountDirections(topology, 3) == 4);
	test_assert(CountDirections(topology, 4) == 4);
	test_assert(CountDirections(topology, 5) == 4);
	test_assert(CountDirections(topology, 6) == 4);
	test_assert(CountDirections(topology, 7) == 4);
	test_assert(CountDirections(topology, 8) == 4);
	test_assert(CountDirections(topology, 9) == 4);
	test_assert(CountDirections(topology, 10) == 4);
	test_assert(CountDirections(topology, 11) == 4);

	// Sanity check
	test_assert(GetReceiver(topology, 5, DIRECTION_NE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_NW) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_SE) == INVALID_DIRECTION);
	test_assert(GetReceiver(topology, 5, DIRECTION_SW) == INVALID_DIRECTION);

	// Test GetAllReceivers
	lp_id_t receivers[CountDirections(topology, 3)];
	GetAllReceivers(topology, 3, receivers);
	test_assert(receivers[0] == 0);
	test_assert(receivers[1] == 2);
	test_assert(receivers[2] == 11);
	test_assert(receivers[3] == 7);

	// Test random receiver
	for(unsigned i = 0; i < RANDOM_TRIALS; i++) {
		for(unsigned j = 0; j < 12; j++) // 12 is the number of regions in this test
			test_assert(GetReceiver(topology, j, DIRECTION_RANDOM) < CountRegions(topology));
	}

	// Test neighbor check
	test_assert(IsNeighbor(topology, 0, 1) == true);
	test_assert(IsNeighbor(topology, 0, 4) == true);
	test_assert(IsNeighbor(topology, 5, 10) == false);
	test_assert(IsNeighbor(topology, 11, 8) == true);
	test_assert(IsNeighbor(topology, 3, 11) == true);
	test_assert(IsNeighbor(topology, 3, 1) == false);

	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Ring topology", test_ring, NULL);
	test("BidRing topology", test_bidring, NULL);
	test("Torus topology", test_torus, NULL);
}
