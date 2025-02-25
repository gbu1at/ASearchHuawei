//
// Created by apple on 04.07.2024.
//

#ifndef ASEARCH_A_SEARCH_EFFICIENCY_H
#define ASEARCH_A_SEARCH_EFFICIENCY_H

#include "../includes/structures.h"
#include "../ALGO/asearch.h"
#include "../generate/generate_graphs.h"
#include "../LANDMARKS/landmarks.h"
#include <random>
#include <iostream>
#include <string>

CH::AlgorithmEfficiency a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                            const CH::LandMarks& lm
);

CH::AlgorithmEfficiency B_a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                              const CH::LandMarks& lm);

//CH::AlgorithmEfficiency
//a_search_manhattan_distance_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::GridGraph &graph,
//                                       bool is_B_search = false);
//
//CH::AlgorithmEfficiency
//a_search_manhattan_distance_average_efficiency(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::GridGraph &graph,
//                                       bool is_B_search = false);


CH::AlgorithmEfficiency
a_search_landmarks_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, CH::LandMarks& lm,
                              bool is_B_search = false);


CH::AlgorithmEfficiency
a_search_landmarks_average_efficiency(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::Graph &graph, CH::LandMarks &lm,
                                      bool is_B_search = false);


#endif //ASEARCH_A_SEARCH_EFFICIENCY_H
