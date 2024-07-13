//
// Created by apple on 05.07.2024.
//

#ifndef ASEARCH_DIJKSTRA_EFFICIENCY_H
#define ASEARCH_DIJKSTRA_EFFICIENCY_H

#include "../includes/structures.h"
#include "../ALGO/dijkstra.h"


CH::AlgorithmEfficiency dijkstra_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, bool is_B_search = false);

CH::AlgorithmEfficiency dijkstra_average_efficiency(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::Graph& graph, bool is_B_search = false);

#endif //ASEARCH_DIJKSTRA_EFFICIENCY_H
