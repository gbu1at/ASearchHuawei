//
// Created by apple on 04.07.2024.
//

#include "test_efficiency.h"




void test_manhattan_graph_efficiency(int seed) {
    std::mt19937 rnd(seed);

    int rows = 5000, cols = 5000, cnt_block = rows * cols / 4;
    int n = rows * cols;

    auto get_cell = [cols](CH::vertex_t id) {
        return std::make_pair(id / cols, id % cols);
    };

    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    CH::GridGraph graph = generate_random_grid_graph(rows, cols, cnt_block, seed);

    CH::vertex_t start = rnd() % n;
    CH::vertex_t finish = rnd() % n;

    while (graph.vertices[start].degree() == 0 || graph.vertices[finish].degree() == 0) {
        start = rnd() % n;
        finish = rnd() % n;
    }

    auto [finish_row, finish_col] = get_cell(finish);
    auto [start_row, start_col] = get_cell(start);

    CH::AlgorithmEfficiency E_a_search = a_search_manhattan_distance_efficiency(start, finish, graph);
    CH::AlgorithmEfficiency E_B_a_search = a_search_manhattan_distance_efficiency(start, finish, graph, true);
    CH::AlgorithmEfficiency E_dijkstra = dijkstra_efficiency(start, finish, graph);
    CH::AlgorithmEfficiency E_B_dijkstra = B_dijkstra_efficiency(start, finish, graph);

    std::cout << "\n------------------------------------------------------------------------------------------\n";
    std::cout << "setting\n";
    std::cout << "rows: " << rows << "\tcols: " << cols << "\n";
    std::cout << "manhattan distance: "
              << abs((int) finish_col - (int) start_col) + abs((int) finish_row - (int) start_row) << "\n";
    std::cout << "algorithms:\n";

    E_a_search.print();
    E_B_a_search.print();
    E_dijkstra.print();
    E_B_dijkstra.print();
    std::cout << "\n------------------------------------------------------------------------------------------\n";
}