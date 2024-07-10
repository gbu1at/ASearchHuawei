//
// Created by apple on 03.07.2024.
//

#ifndef ASEARCH_ASEARCH_H
#define ASEARCH_ASEARCH_H

#include "../includes/structures.h"

/*
    a search между двумя вергинами в графе
    p - это 'хороший' массив расстояний
    p - является оценкой снизу на расстояние между вершинами v и t
    p[finish] = 0
*/


struct ASearch {
    static void init(const CH::Graph &graph);

    static const CH::Graph *graph;

    static CH::weight_t a_search(CH::vertex_t start, CH::vertex_t finish, std::function<CH::weight_t(CH::vertex_t)> p,
                                 double *percent = nullptr, std::vector<bool> *mark_ = nullptr, int *cnt_move_ = nullptr,
                                 int *cnt_edge_in_way_ = nullptr);

    static std::vector<std::pair<CH::weight_t, int>> distances;
    static std::vector<std::pair<bool, int>> mark;
    static std::vector<std::pair<size_t, int>> min_way;
    static std::vector<std::pair<CH::weight_t, int>> k;
    static int T;
};


struct BASearch {
    static void init(const CH::Graph &graph);

    static const CH::Graph *graph;
    static int T;

    static CH::weight_t
    B_a_search(CH::vertex_t start, CH::vertex_t finish,
               std::function<CH::weight_t(CH::vertex_t)> p_s,
               std::function<CH::weight_t(CH::vertex_t)> p_f,
               double *percent = nullptr, std::vector<bool> *mark_ = nullptr, int *cnt_move_ = nullptr,
               int *cnt_edge_in_way_ = nullptr);

    static std::vector<std::pair<CH::weight_t, int>> distances_start;
    static std::vector<std::pair<CH::weight_t, int>> distances_finish;
    static std::vector<std::pair<CH::weight_t, int>> k_s;
    static std::vector<std::pair<CH::weight_t, int>> k_f;
    static std::vector<std::pair<bool, int>> mark_from_start;
    static std::vector<std::pair<bool, int>> mark_from_finish;
    static std::vector<std::pair<int, int>> min_way_s;
    static std::vector<std::pair<int, int>> min_way_f;
    static std::vector<std::pair<bool, int>> mark;
};

// a_search с двойным запуском ( из вершин finish и start )


#endif //ASEARCH_ASEARCH_H
