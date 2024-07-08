//
// Created by apple on 05.07.2024.
//

#ifndef ASEARCH_TEST_EFFICIENCY_LANDMARKS_H
#define ASEARCH_TEST_EFFICIENCY_LANDMARKS_H


#include "../includes/structures.h"

CH::AlgorithmEfficiency
a_search_landmarks_average_efficiency_smart_lm(
        const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> &pair_start_finish, const CH::Graph &graph,
        int cnt_landmarks = 1, bool is_B_search = false);

CH::AlgorithmEfficiency a_search_landmarks_average_efficiency_random_lm(
        const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> &pair_start_finish, const CH::Graph &graph,
        int cnt_landmarks = 1, bool is_B_search = false);


#endif //ASEARCH_TEST_EFFICIENCY_LANDMARKS_H
