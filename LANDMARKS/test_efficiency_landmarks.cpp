//
// Created by apple on 05.07.2024.
//

#include "test_efficiency_landmarks.h"
#include "../TEST/efficiency/a_search_efficiency.h"


CH::AlgorithmEfficiency
a_search_landmarks_average_efficiency_smart_lm(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::Graph &graph, int cnt_landmarks, bool is_B_search) {
    CH::LandMarks lm;
    lm.smart_landmarks(cnt_landmarks, graph);
    return a_search_landmarks_average_efficiency(pair_start_finish, graph, lm, is_B_search);
}

CH::AlgorithmEfficiency a_search_landmarks_average_efficiency_random_lm(
        const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::Graph &graph,
        int cnt_landmarks, bool is_B_search) {
    CH::LandMarks lm;
    lm.random_landmarks(cnt_landmarks, graph);
    return a_search_landmarks_average_efficiency(pair_start_finish, graph, lm, is_B_search);
}
