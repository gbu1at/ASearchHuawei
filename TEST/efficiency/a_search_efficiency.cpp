//
// Created by apple on 04.07.2024.
//

#include "a_search_efficiency.h"


CH::AlgorithmEfficiency a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                            const std::vector<CH::weight_t> &p) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    E.result = a_search(start, finish, graph, p, &E.percent);
    E.name_algorithm = "a_search";

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}


CH::AlgorithmEfficiency dijkstra_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    E.result = dijkstra_min_two_vertices(start, finish, graph, &E.percent);
    E.name_algorithm = "dijkstra";

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}


CH::AlgorithmEfficiency B_dijkstra_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    E.result = B_dijkstra_min_two_vertices(start, finish, graph, &E.percent);
    E.name_algorithm = "B_dijkstra";

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}


CH::AlgorithmEfficiency B_a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                              const std::vector<CH::weight_t> &p_s,
                                              const std::vector<CH::weight_t> &p_f) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    E.result = B_a_search(start, finish, graph, p_s, p_f, &E.percent);
    E.name_algorithm = "B_a_search";

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}


CH::AlgorithmEfficiency a_search_manhattan_distance_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::GridGraph &graph, bool is_B_search) {

    size_t rows = graph.rows, cols = graph.cols;
    size_t n = graph.n;

    auto get_cell = [cols](CH::vertex_t id) {
        return std::make_pair(id / cols, id % cols);
    };

    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    std::vector<CH::weight_t> p_s(n), p_f(n);

    auto[start_row, start_col] = get_cell(start);
    auto[finish_row, finish_col] = get_cell(finish);

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col) {
            p_s[get_id(row, col)] = abs((int)finish_row - row) + abs((int)finish_col - col);
            p_f[get_id(row, col)] = abs((int)start_row - row) + abs((int)start_col - col);
        }

    CH::AlgorithmEfficiency E;
    if (!is_B_search)
        E = a_search_efficiency(start, finish, graph, p_s);
    else
        E = B_a_search_efficiency(start, finish, graph, p_s, p_f);

    return E;
}
