//
// Created by apple on 04.07.2024.
//

#include "a_search_test.h"


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

    {
        CH::Graph graph(8);
        graph.add_edge(0, 1, 1);
        graph.add_edge(1, 2, 2);
        graph.add_edge(2, 3, 1);
        graph.add_edge(3, 4, 4);
        graph.add_edge(4, 5, 1);
        graph.add_edge(5, 6, 3);
        graph.add_edge(6, 7, 1);
        graph.add_edge(0, 7, 10);

        auto result = dijkstra_min_all_vertices(0, graph);

        assert(result[0] == 0);
        assert(result[1] == 1);
    }

    {
        CH::Graph graph(30);

        for (CH::vertex_t i = 0; i < 29; ++i)
            graph.add_edge(i, i + 1, i + 2);

        graph.add_edge(0, 15, 10);
        graph.add_edge(10, 20, 15);
        graph.add_edge(5, 25, 7);
        graph.add_edge(2, 28, 8);

        auto result = dijkstra_min_all_vertices(0, graph);

        assert(result[0] == 0);
        assert(result[15] == 10);
        assert(result[25] == 27);
        assert(result[28] == 13);
    }

    std::cout << "test_simple_dijkstra tests completed!" << std::endl;
}


void test_a_search_null_p() {

    CH::vertex_t n = 100;
    size_t m = 700;
    CH::weight_t max_weight = 5;
    std::vector<CH::weight_t> p(n, 0);

    CH::Graph rnd_graph = generate_random_graph(n, m, max_weight);


    std::function<CH::weight_t(CH::vertex_t)> dist_func_p = [&p](CH::vertex_t id) {
        return p[id];
    };

    for (int v = 0; v < n; ++v)
        for (int u = 0; u < n; ++u) {
            assert(dijkstra_min_two_vertices(u, v, rnd_graph) == a_search(u, v, rnd_graph,
                                                                          dist_func_p));
        }

    std::cout << "test_a_search_null_p work correct!\n";
}