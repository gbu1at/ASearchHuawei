//
// Created by apple on 05.07.2024.
//

#include "efficiency_landmarks.h"
#include "../efficiency/a_search_efficiency.h"


CH::AlgorithmEfficiency
a_search_landmarks_average_efficiency_smart_lm(
        const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> &pair_start_finish, const CH::Graph &graph,
        int cnt_landmarks, int active_landmarks, bool is_B_search) {
    CH::LandMarks lm;
    if (active_landmarks == 0) active_landmarks = cnt_landmarks;
    lm.smart_landmarks(cnt_landmarks, active_landmarks, graph);
    return a_search_landmarks_average_efficiency(pair_start_finish, graph, lm, is_B_search);
}

CH::AlgorithmEfficiency a_search_landmarks_average_efficiency_random_lm(
        const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> &pair_start_finish, const CH::Graph &graph,
        int cnt_landmarks, int active_landmarks, bool is_B_search) {
    CH::LandMarks lm;
    if (active_landmarks == 0) active_landmarks = cnt_landmarks;
    lm.random_landmarks(cnt_landmarks, active_landmarks, graph);
    return a_search_landmarks_average_efficiency(pair_start_finish, graph, lm, is_B_search);
}
