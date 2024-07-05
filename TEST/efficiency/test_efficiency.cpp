//
// Created by apple on 04.07.2024.
//

#include "test_efficiency.h"
#include <cassert>
#include "../../LANDMARKS/landmarks.h"


void test_manhattan_graph_efficiency() {
    int rows = 1000, cols = 1000, cnt_block = rows * cols / 4;
    int n = rows * cols;

    auto get_cell = [cols](CH::vertex_t id) {
        return std::make_pair(id / cols, id % cols);
    };

    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    CH::GridGraph graph = generate_random_grid_graph(rows, cols, cnt_block);

    CH::vertex_t start = RandomUtil::PROJECT_RND() % n;
    CH::vertex_t finish = RandomUtil::PROJECT_RND() % n;

    while (graph.vertices[start].degree() == 0 || graph.vertices[finish].degree() == 0) {
        start = RandomUtil::PROJECT_RND() % n;
        finish = RandomUtil::PROJECT_RND() % n;
    }

    auto [finish_row, finish_col] = get_cell(finish);
    auto [start_row, start_col] = get_cell(start);


    CH::AlgorithmEfficiency E_a_search = a_search_manhattan_distance_efficiency(start, finish, graph);
    CH::AlgorithmEfficiency E_B_a_search = a_search_manhattan_distance_efficiency(start, finish, graph, true);
    CH::AlgorithmEfficiency E_dijkstra = dijkstra_efficiency(start, finish, graph);
    CH::AlgorithmEfficiency E_B_dijkstra = B_dijkstra_efficiency(start, finish, graph);

    std::vector<CH::weight_t> results = {E_a_search.result, E_B_a_search.result, E_dijkstra.result,
                                         E_B_dijkstra.result};

    assert(std::all_of(results.begin(), results.end(), [&results](CH::weight_t x) { return x == results[0]; }));

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


void test_random_graph_efficiency(int cnt_landmarks) {
    CH::vertex_t n = 100000;
    int m = 500000;
    CH::weight_t max_w = 10;

    CH::Graph graph = generate_random_graph(n, m, max_w);
//    graph.print();
    CH::vertex_t start = RandomUtil::PROJECT_RND() % n;
    CH::vertex_t finish = RandomUtil::PROJECT_RND() % n;

    CH::AlgorithmEfficiency E_a_search = a_search_graph_rnd_landmarks_efficiency(start, finish, graph, cnt_landmarks);
    CH::AlgorithmEfficiency E_B_a_search = a_search_graph_rnd_landmarks_efficiency(start, finish, graph, cnt_landmarks, true);
    CH::AlgorithmEfficiency E_dijkstra = dijkstra_efficiency(start, finish, graph);
    CH::AlgorithmEfficiency E_B_dijkstra = B_dijkstra_efficiency(start, finish, graph);

    std::vector<CH::weight_t> results = {E_a_search.result, E_B_a_search.result, E_dijkstra.result,
                                         E_B_dijkstra.result};

    assert(std::all_of(results.begin(), results.end(), [&results](CH::weight_t x) { return x == results[0]; }));

    std::cout << "\n------------------------------------------------------------------------------------------\n";
    std::cout << "setting\n";
    std::cout << "vertexes: " << n << "\tedges: " << m << "\n";
    std::cout << "algorithms:\n";

    E_a_search.print();
    E_B_a_search.print();
    E_dijkstra.print();
    E_B_dijkstra.print();
    std::cout << "\n------------------------------------------------------------------------------------------\n";

}
