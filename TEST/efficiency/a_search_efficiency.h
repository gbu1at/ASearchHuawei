//
// Created by apple on 04.07.2024.
//

#ifndef ASEARCH_A_SEARCH_EFFICIENCY_H
#define ASEARCH_A_SEARCH_EFFICIENCY_H

#include "../../includes/structures.h"
#include "../../ALGO/asearch.h"
#include "../../ALGO/dijkstra.h"
#include "../../generate/generate_graphs.h"
#include <random>
#include <iostream>
#include <string>

CH::AlgorithmEfficiency a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                            std::function<CH::weight_t(CH::vertex_t)> p
);

CH::AlgorithmEfficiency dijkstra_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph);

CH::AlgorithmEfficiency B_dijkstra_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph);

CH::AlgorithmEfficiency B_a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                              std::function<CH::weight_t(CH::vertex_t)> p_s,
                                              std::function<CH::weight_t(CH::vertex_t)> p_f);

CH::AlgorithmEfficiency
a_search_manhattan_distance_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::GridGraph &graph,
                                       bool is_B_search = false);


CH::AlgorithmEfficiency
a_search_graph_rnd_landmarks_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, int cnt,
                                        bool is_B_search = false);


#endif //ASEARCH_A_SEARCH_EFFICIENCY_H
