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
CH::weight_t
a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, std::function<CH::weight_t(CH::vertex_t)> p,
            double *percent = nullptr, std::vector<bool> *mark_ = nullptr, int *cnt_move_ = nullptr, int *cnt_edge_in_way_ = nullptr);

// a_search с двойным запуском ( из вершин finish и start )
CH::weight_t
B_a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, std::function<CH::weight_t(CH::vertex_t)> p_s,
           std::function<CH::weight_t(CH::vertex_t)> p_f,
           double *percent = nullptr, std::vector<bool>* mark_ = nullptr, int *cnt_move_ = nullptr, int *cnt_edge_in_way_ = nullptr);


#endif //ASEARCH_ASEARCH_H
