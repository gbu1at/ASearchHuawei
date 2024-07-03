//
// Created by apple on 02.07.2024.
//

#ifndef ASEARCH_DIJKSTRA_H
#define ASEARCH_DIJKSTRA_H

#include "../includes/structures.h"
#include <vector>


// возвращает минимальные расстояния от вершины start до всех вершин
std::vector<CH::weight_t> dijkstra_min_all_vertices(CH::vertex_t start, const CH::Graph& graph);

// возвращает минимальные расстояния от вершины start до вершины finish
CH::weight_t dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph& graph);

// возвращает минимальные расстояния от вершины start до вершины finish, но отличается реализацией тем, что
// данная задача будет решаться с помощью двойного запуска из start и finish
CH::weight_t B_dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph& graph);

#endif //ASEARCH_DIJKSTRA_H
