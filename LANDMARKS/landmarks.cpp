//
// Created by apple on 04.07.2024.
//

#include "landmarks.h"
#include <random>
#include "../ALGO/dijkstra.h"


void CH::LandMarks::random_landmarks(size_t cnt, const CH::Graph &graph, size_t seed) {
    this->init(cnt);

    std::mt19937 rnd(seed);

    std::iota(landmarks.begin(), landmarks.end(), 0);
    std::shuffle(landmarks.begin(), landmarks.end(), rnd);
    landmarks.resize(cnt);


    for (int lm = 0; lm < cnt; ++lm)
        min_dist_for_landmarks[lm] = dijkstra_min_all_vertices(landmarks[lm], graph);

}

void CH::LandMarks::smart_landmarks(size_t cnt, const CH::Graph &graph) {
    this->init(cnt);
}

CH::weight_t CH::LandMarks::get_dist(int finish, int v) {
    auto result = std::numeric_limits<weight_t>::min();
    for (int lm = 0; lm < cnt; ++lm)
        result = std::max(result, abs(min_dist_for_landmarks[lm][finish] -
                                      min_dist_for_landmarks[lm][v]));
    return result;
}


void CH::LandMarks::init(int cnt) {
    this->cnt = cnt;
    landmarks.assign(cnt, -1);
    min_dist_for_landmarks.assign(cnt, {});
}
