//
// Created by apple on 02.07.2024.
//

#ifndef ASEARCH_DIJKSTRA_H
#define ASEARCH_DIJKSTRA_H

#include "../includes/structures.h"
#include <vector>


struct Dijkstra {
    static std::vector<std::pair<CH::weight_t, int>> distances;

    static void init(const CH::Graph &graph);

    static int T;
    static std::vector<std::pair<size_t, int>> min_way;


    static CH::weight_t
    dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                              double *percent = nullptr,
                              int *cnt_move = nullptr, int *cnt_edge_in_way_ = nullptr,
                              std::vector<CH::vertex_t> *vertex_min_way = nullptr);
};

struct BDijkstra {
    static int T;

    static void init(const CH::Graph &graph);

    static std::vector<std::pair<CH::weight_t, int>> distances_start;
    static std::vector<std::pair<CH::weight_t, int>> distances_finish;

    static std::vector<std::pair<bool, int>> mark_from_start;
    static std::vector<std::pair<bool, int>> mark_from_finish;
    static std::vector<std::pair<size_t, int>> min_way_s;
    static std::vector<std::pair<size_t, int>> min_way_f;

    static CH::weight_t
    B_dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                double *percent = nullptr,
                                int *cnt_move = nullptr, int *cnt_edge_in_way_ = nullptr);
};

// возвращает минимальные расстояния от вершины start до всех вершин
std::vector<CH::weight_t> dijkstra_min_all_vertices(CH::vertex_t start, const CH::Graph &graph);

// возвращает минимальные расстояния от вершины start до вершины finish
//CH::weight_t dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph& graph, double* percent = nullptr, int *cnt_move = nullptr, int *cnt_edge_in_way_ = nullptr);

// возвращает минимальные расстояния от вершины start до вершины finish, но отличается реализацией тем, что
// данная задача будет решаться с помощью двойного запуска из start и finish
//CH::weight_t B_dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph& graph, double* percent = nullptr, int* cnt_move = nullptr, int *cnt_edge_in_way = nullptr);

#endif //ASEARCH_DIJKSTRA_H
