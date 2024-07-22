/**
 * @file test/tests/lib/topology.c
 *
 * @brief Test: topology library
 *
 * SPDX-FileCopyrightText: 2008-2022 HPDCS Group <rootsim@googlegroups.com>
 * SPDX-License-Identifier: GPL-3.0-only
 */
#include <limits.h>

#include <test.h>
#include <ROOT-Sim/topology.h>
#include <string.h>

const enum topology_geometry LAST_TOPOLOGY_WITH_TWO_PARAMETERS = TOPOLOGY_TORUS;
const enum topology_geometry LAST_TOPOLOGY_VALID_VALUE = TOPOLOGY_GRAPH;
const enum topology_direction LAST_DIRECTION_VALID_VALUE = DIRECTION_SE;

#define MAX_NODES_TEST 100
#define NUM_QUERIES 500

#define unique_ptr(num1, num2) (void *)(((unsigned long long)num1 << 32) | (unsigned long long)num2)

static int test_graph(_unused void *_)
{
	struct topology *topology;
	unsigned num_edges;
	lp_id_t from, to;

	for(unsigned nodes = 1; nodes < MAX_NODES_TEST; nodes++) {
		topology = InitializeTopology(TOPOLOGY_GRAPH, nodes);

		num_edges = (unsigned)(nodes + (double)test_random_u() / ((double)ULLONG_MAX / (9 * nodes + 1) + 1));
		for(unsigned edge = 0; edge < num_edges; edge++) {
			from = test_random_range(nodes);
			to = test_random_range(nodes);
			test_assert(AddTopologyLink(topology, from, to, test_random_double()));
			test_assert(AddTopologyLink(topology, from, to, 2.0) == false);
			test_assert(AddTopologyLink(topology, from, to, -1.0) == false);
			test_assert(SetTopologyLinkData(topology, from, to, unique_ptr(from, to)) == true);
		}

		for(unsigned i = 0; i < NUM_QUERIES; i++) {
			from = test_random_range(nodes);
			to = GetReceiver(topology, from, DIRECTION_RANDOM);

			// We get an invalid direction only if there is a node with no
			// outgoing edges. In this case, we check this condition.
			if(to == INVALID_DIRECTION) {
				test_assert(CountDirections(topology, from) == 0);
				continue;
			}

			test_assert(to < nodes);
			test_assert(IsNeighbor(topology, from, to));
			test_assert(GetTopologyLinkData(topology, from, to) == unique_ptr(from, to));
		}

		ReleaseTopology(topology);
	}

	// Test GetAllReceivers
	topology = InitializeTopology(TOPOLOGY_GRAPH, 6);
	AddTopologyLink(topology, 0, 1, 1);
	AddTopologyLink(topology, 1, 2, 1);
	AddTopologyLink(topology, 1, 3, 1);
	AddTopologyLink(topology, 3, 5, 1);
	AddTopologyLink(topology, 4, 5, 1);
	lp_id_t receivers[2];
	memset(receivers, 0, sizeof(receivers));
	GetAllReceivers(topology, 0, receivers);
	test_assert(receivers[0] == 1);
	test_assert(receivers[1] == 0);
	memset(receivers, 0, sizeof(receivers));
	GetAllReceivers(topology, 1, receivers);
	test_assert(receivers[0] == 2);
	test_assert(receivers[1] == 3);
	memset(receivers, 0, sizeof(receivers));
	GetAllReceivers(topology, 3, receivers);
	test_assert(receivers[0] == 5);
	test_assert(receivers[1] == 0);
	memset(receivers, 0, sizeof(receivers));
	GetAllReceivers(topology, 4, receivers);
	test_assert(receivers[0] == 5);
	test_assert(receivers[1] == 0);
	ReleaseTopology(topology);

	// Test link normalization
	topology = InitializeTopology(TOPOLOGY_GRAPH, 3);
	AddTopologyLink(topology, 0, 1, 1);
	AddTopologyLink(topology, 0, 2, 1);
	test_assert(NormalizeLinkProbabilities(topology));
	bool dest[2] = {false, false};
	for(int i = 0; i < 100; i++) {
		dest[GetReceiver(topology, 0, DIRECTION_RANDOM) - 1] = true;
	}
	test_assert(dest[0]);
	test_assert(dest[1]);
	ReleaseTopology(topology);

	// Test sanity checks on graphs
	topology = InitializeTopology(TOPOLOGY_GRAPH, 1);
	for(enum topology_direction i = 0; i <= LAST_DIRECTION_VALID_VALUE; i++)
		test_assert(GetReceiver(topology, 0, i) == INVALID_DIRECTION);
	ReleaseTopology(topology);

	return 0;
}


int main(void)
{
	test("Graph topology", test_graph, NULL);
}
