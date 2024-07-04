//
// Created by apple on 04.07.2024.
//

#ifndef ASEARCH_LANDMARKS_H
#define ASEARCH_LANDMARKS_H

#include <vector>
#include "../includes/structures.h"
#include <ctime>

namespace CH {
    struct LandMarks {
        int cnt;
        std::vector<vertex_t> landmarks;
        std::vector<std::vector<weight_t>> min_dist_for_landmarks;

        void random_landmarks(size_t cnt, const Graph &graph, size_t seed = time(nullptr));

        void smart_landmarks(size_t cnt, const Graph &graph);

        void smart_landmark1(size_t cnt, const Graph &graph);

        void smart_landmarks2(size_t cnt, const GridGraph &graph);

        CH::weight_t get_dist(int finish, int v);

    private:
        void init(int cnt);
    };
};


#endif //ASEARCH_LANDMARKS_H
