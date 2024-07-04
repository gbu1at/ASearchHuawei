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
a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, const std::vector<CH::weight_t> &p,
         double *percent = nullptr);

// a_search с двойным запуском ( из вершин finish и start )
CH::weight_t
B_a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, const std::vector<CH::weight_t> &p_s,
           const std::vector<CH::weight_t> &p_f,
           double *percent = nullptr);


#endif //ASEARCH_ASEARCH_H
