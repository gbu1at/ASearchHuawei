//
// Created by apple on 04.07.2024.
//

#ifndef ASEARCH_LANDMARKS_H
#define ASEARCH_LANDMARKS_H

#include <vector>
#include "../includes/structures.h"
#include <ctime>
#include <map>

namespace CH {
    struct LandMarks {
        size_t cnt_landmarks;
        int finish = 0;
        std::vector<vertex_t> landmarks;
        std::vector<std::vector<weight_t>> min_dist_for_landmarks;
        std::vector<int> active_landmarks;
        int cnt_active_lm;
//        std::vector<std::vector<std::pair<CH::weight_t, CH::vertex_t >>> far_lm_for_ver;

        LandMarks() {}

        LandMarks(const Graph &graph, const std::vector<vertex_t> &new_land_marks) {
            this->landmarks = new_land_marks;
            this->cnt_landmarks = new_land_marks.size();
            this->build_min_ways(graph);
        }

        void random_landmarks(size_t cnt_landmarks, size_t cnt_active_landmarks, const Graph &graph);

        void smart_landmarks(size_t cnt_landmarks, size_t cnt_active_landmarks, const Graph &graph);

        void set_start_finish(vertex_t start, vertex_t finish);

        void smart_landmark1(size_t cnt_landmarks, size_t cnt_active_landmarks, const Graph &graph);

        void smart_landmarks2(size_t cnt_landmarks, size_t cnt_active_landmarks, const GridGraph &graph);

        void build_min_ways(const CH::Graph &graph);


        CH::weight_t get_dist(CH::vertex_t v, CH::vertex_t u) const;

        std::map<int, int> mp;

    private:
        void init_landmarks(int cnt_landmarks, int cnt_active_landmarks);
    };

};


#endif //ASEARCH_LANDMARKS_H
