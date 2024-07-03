//
// Created by apple on 03.07.2024.
//

#ifndef ASEARCH_A_SEARCH_TEST_H
#define ASEARCH_A_SEARCH_TEST_H

#include "../includes/structures.h"
#include "../generate/generate_graphs.h"
#include "../includes/writing.h"
#include "../ALGO/dijkstra.h"
#include "../ALGO/asearch.h"
#include <cassert>

void test_simple_dijkstra() {
    {
        CH::Graph graph(6);
        graph.add_edge(0, 1, 7);
        graph.add_edge(0, 2, 9);
        graph.add_edge(0, 5, 14);
        graph.add_edge(1, 2, 10);
        graph.add_edge(1, 3, 15);
        graph.add_edge(2, 3, 11);
        graph.add_edge(2, 5, 2);
        graph.add_edge(3, 4, 6);
        graph.add_edge(4, 5, 9);

        auto result = dijkstra_min_all_vertices(0, graph);

        assert(result[0] == 0);
        assert(result[1] == 7);
        assert(result[2] == 9);
        assert(result[3] == 20);
        assert(result[4] == 20);
        assert(result[5] == 11);
    }

    {
        CH::Graph graph(7);
        graph.add_edge(0, 1, 2);
        graph.add_edge(0, 2, 4);
        graph.add_edge(1, 2, 1);
        graph.add_edge(1, 3, 7);
        graph.add_edge(2, 4, 3);
        graph.add_edge(3, 5, 1);
        graph.add_edge(4, 5, 5);
        graph.add_edge(4, 6, 8);
        graph.add_edge(5, 6, 2);

        auto result = dijkstra_min_all_vertices(0, graph);

        assert(result[0] == 0);
        assert(result[1] == 2);
        assert(result[2] == 3);
        assert(result[3] == 9);
        assert(result[4] == 6);
        assert(result[5] == 10);
        assert(result[6] == 12);
    }

    std::cout << "tests completed!" << std::endl;
}


void test_a_search_null_p() {
    int seed = 3224;

    CH::vertex_t n = 8;
    size_t m = 15;
    CH::weight_t max_weight = 5;
    std::vector<CH::weight_t> p(n, 0);

    CH::Graph rnd_graph = generate_random_graph(n, m, max_weight, seed);

    writing_graph(rnd_graph, std::cout);

    for (int v = 0; v < n; ++v)
        for (int u = 0; u < n; ++u) {
            assert(dijkstra_min_two_vertices(u, v, rnd_graph) == a_search(u, v, rnd_graph, p));
        }

    std::cout << "work correct!\n";
}

void test_a_search_manhattan_distance() {
    int seed = 234;
}

#endif //ASEARCH_A_SEARCH_TEST_H
