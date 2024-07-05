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

CH::AlgorithmEfficiency dijkstra_average_efficiency(int tests, const CH::Graph& graph, bool is_B_search) {
    double average_percent = 0;
    double average_time = 0;
    CH::weight_t result = 0;
    int cnt_move = 0;
    int cnt_edge_in_way = 0;

    for (int _ = 0; _ < tests; ++_) {
        CH::vertex_t start = Setting::PROJECT_RND() % graph.n;
        CH::vertex_t finish = Setting::PROJECT_RND() % graph.n;

        CH::AlgorithmEfficiency E = dijkstra_efficiency(start, finish, graph, is_B_search);
        average_percent += E.percent;
        average_time += E.time;
        result += E.result;
        cnt_move += E.cnt_move;
        cnt_edge_in_way += E.cnt_edge_in_way;
    }
    CH::AlgorithmEfficiency E;
    E.percent = average_percent / tests;
    E.time = average_time / tests;
    E.result = result / tests;
    E.cnt_move = cnt_move / tests;
    E.cnt_edge_in_way = cnt_edge_in_way / tests;
    if (!is_B_search) E.name_algorithm = "dijkstra";
    else E.name_algorithm = "B + dijkstra";

    return E;
}

