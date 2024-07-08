//
// Created by apple on 05.07.2024.
//

#include "dijkstra_efficiency.h"


CH::AlgorithmEfficiency dijkstra_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, bool is_B_search) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    if (!is_B_search) {
        E.result = dijkstra_min_two_vertices(start, finish, graph, &E.percent, &E.cnt_move, &E.cnt_edge_in_way);
        E.name_algorithm = "dijkstra";
    } else {
        E.result = B_dijkstra_min_two_vertices(start, finish, graph, &E.percent, &E.cnt_move, &E.cnt_edge_in_way);
        E.name_algorithm = "B_dijkstra";
    };

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}

CH::AlgorithmEfficiency dijkstra_average_efficiency(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::Graph& graph, bool is_B_search) {
    double average_percent = 0;
    double average_time = 0;
    CH::weight_t result = 0;
    int cnt_move = 0;
    int cnt_edge_in_way = 0;
    int N = 0;

    int tests = pair_start_finish.size();

    for (int _ = 0; _ < tests; ++_) {
        auto[start, finish] = pair_start_finish[_];

        CH::AlgorithmEfficiency E = dijkstra_efficiency(start, finish, graph, is_B_search);
        if (E.result != std::numeric_limits<CH::weight_t>::max()) {
            average_percent += E.percent;
            average_time += E.time;
            result += E.result;
            cnt_move += E.cnt_move;
            cnt_edge_in_way += E.cnt_edge_in_way;
            N ++;
        }
    }
    CH::AlgorithmEfficiency E;
    E.percent = average_percent / N;
    E.time = average_time / N;
    E.result = result / N;
    E.cnt_move = cnt_move / N;
    E.cnt_edge_in_way = cnt_edge_in_way / N;
    if (!is_B_search) E.name_algorithm = "dijkstra";
    else E.name_algorithm = "B + dijkstra";

    return E;
}

