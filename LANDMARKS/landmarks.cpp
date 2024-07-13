//
// Created by apple on 04.07.2024.
//

#include "landmarks.h"
#include <random>
#include "../ALGO/dijkstra.h"
#include <cassert>
#include <map>
#include <set>
#include <iostream>


CH::vertex_t generate_new_landmark(const CH::Graph &graph, const std::vector<CH::vertex_t> &landmarks) {
    std::vector<CH::weight_t> dist(graph.n, -1);


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertex;

    for (auto v: landmarks) {
        dist[v] = 0;
        active_vertex.insert({0, v});
    }

    while (!active_vertex.empty()) {
        auto [d, v] = *active_vertex.begin();
        active_vertex.erase(active_vertex.begin());

        for (auto e: graph.vertices[v].adj) {
            if (dist[e.to] == -1 || dist[e.to] > dist[v] + e.weight) {
                active_vertex.erase({dist[e.to], e.to});
                dist[e.to] = dist[v] + e.weight;
                active_vertex.insert({dist[e.to], e.to});
            }
        }
    }
    CH::vertex_t new_landmark = landmarks[0];
    for (int v = 0; v < graph.n; ++v)
        if (dist[v] > dist[new_landmark])
            new_landmark = v;
//    std::cout << dist[new_landmark] << "\n";
    return new_landmark;
}

CH::vertex_t get_center_graph(const CH::Graph &graph) {
    CH::vertex_t v = Setting::PROJECT_RND() & graph.n;
    CH::vertex_t u = generate_new_landmark(graph, {v});
    std::vector<CH::vertex_t> min_way;
    Dijkstra::dijkstra_min_two_vertices(v, u, graph, nullptr, nullptr, nullptr, &min_way);
    return min_way[min_way.size() / 2];
}

void CH::LandMarks::random_landmarks(size_t cnt_landmarks, size_t cnt_active_landmarks, const CH::Graph &graph) {
    this->init_landmarks(cnt_landmarks, cnt_active_landmarks);

    landmarks.assign(graph.n, 0);
    std::iota(landmarks.begin(), landmarks.end(), 0);
    Setting::shuffle(landmarks.begin(), landmarks.end());
    landmarks.resize(cnt_landmarks);

    this->build_min_ways(graph);
}

void CH::LandMarks::smart_landmarks(size_t cnt_landmarks, size_t cnt_active_landmarks, const CH::Graph &graph) {
    std::cout << "start find smart landmarks\n";

    this->init_landmarks(cnt_landmarks, cnt_active_landmarks);
//    std::vector<CH::vertex_t> lm_ = {(CH::vertex_t) (Setting::PROJECT_RND() % graph.n)};
//    std::vector<CH::vertex_t> lm = {generate_new_landmark(graph, lm_)};
    std::vector<CH::vertex_t> lm = {get_center_graph(graph)};
    std::cout << "create " << 0 << " landmarks" << "\n";
//    std::cout << lm[0] << "\t";

    for (int i = 1; i < cnt_landmarks; ++i) {
        CH::vertex_t v = generate_new_landmark(graph, lm);
        lm.push_back(v);
        std::cout << "create " << i << " landmarks" << "\n";
    }
    landmarks = lm;

    std::cout << "found smart lm\n";

    this->build_min_ways(graph);
}

//std::map<int, int> CH::mp;


CH::weight_t CH::LandMarks::get_dist(CH::vertex_t v, CH::vertex_t u) const {

//    assert(finish != -1);

    CH::weight_t result = 0;
    int i = 0;
    for (int lm: active_landmarks) {
        CH::weight_t x = abs(min_dist_for_landmarks[lm][u] -
                             min_dist_for_landmarks[lm][v]);
        if (x > result) {
            i = lm;
        }
        result = std::max(result, x);
    }
//    mp[i]++;
    std::cout << "active right now\t" <<  i << "\n";
    return result;
}


void CH::LandMarks::init_landmarks(int cnt_landmarks, int cnt_active_landmarks) {
    this->cnt_landmarks = cnt_landmarks;
    this->cnt_active_lm = cnt_active_landmarks;

    landmarks.assign(cnt_landmarks, -1);
    active_landmarks.assign(cnt_active_lm, -1);
    min_dist_for_landmarks.assign(cnt_landmarks, {});
}


void CH::LandMarks::set_start_finish(CH::vertex_t start, CH::vertex_t finish) {
    CH::LandMarks::finish = finish;

    std::vector<std::pair<int, int>> dist_to_finish_from_start(cnt_landmarks);

    for (int lm = 0; lm < cnt_landmarks; ++lm)
        dist_to_finish_from_start[lm] = {abs(min_dist_for_landmarks[lm][finish] - min_dist_for_landmarks[lm][start]),
                                         lm};

    std::sort(dist_to_finish_from_start.begin(), dist_to_finish_from_start.end());
    std::reverse(dist_to_finish_from_start.begin(), dist_to_finish_from_start.end());

//    std::cout << dist_to_finish_from_start[0].first << "\n";

    int C = 0;

    for (int i = 0; i < cnt_active_lm - 2 * C; ++i) {
        if (i % 2 == 0)
            this->active_landmarks[i] = dist_to_finish_from_start[i / 2].second;
        else
            this->active_landmarks[i] = dist_to_finish_from_start[cnt_landmarks - i / 2 - 1].second;
    }

    std::vector<std::pair<int, int>> dist_to_finish_from_lm(cnt_landmarks);
    std::vector<std::pair<int, int>> dist_to_start_from_lm(cnt_landmarks);
    for (int lm = 0; lm < cnt_landmarks; ++lm) {
        dist_to_finish_from_lm[lm] = {min_dist_for_landmarks[lm][finish], lm};
        dist_to_start_from_lm[lm] = {min_dist_for_landmarks[lm][start], lm};
    }
    std::sort(dist_to_finish_from_lm.begin(), dist_to_finish_from_lm.end());
//    std::reverse(dist_to_finish_from_lm.begin(), dist_to_finish_from_lm.end());

    std::sort(dist_to_start_from_lm.begin(), dist_to_start_from_lm.end());
//    std::reverse(dist_to_start_from_lm.begin(), dist_to_start_from_lm.end());

    for (int i = 0; i < C; ++i)
        this->active_landmarks[cnt_active_lm - 2 * C + i] = dist_to_finish_from_lm[i].second;

    for (int i = 0; i < C; ++i)
        this->active_landmarks[cnt_active_lm - C + i] = dist_to_start_from_lm[i].second;

//    active_landmarks = {1, 5, 8, 17, 37, 38, 41, 53, 67, 68, 69, 74, 77, 81, 84, 87, 95, 96};

//    std::cout << "all landmarks\n";
//    for (int i = 0; i < cnt_landmarks; ++i)
//        std::cout << landmarks[i] << " ";
//    std::cout << "\n";

//    std::cout << "active landmarks\n";
//    for (int i = 0; i < cnt_active_lm; ++i) {
//        int lm = active_landmarks[i];
//        std::cout << lm << ":\t";
//        for (int j = 0; j < cnt_landmarks; ++j)
//            if (dist_to_finish_from_start[j].second == lm)
//                std::cout << dist_to_finish_from_start[j].first << " ";
//        for (int j = 0; j < cnt_landmarks; ++j)
//            if (dist_to_finish_from_lm[j].second == lm)
//                std::cout << dist_to_finish_from_lm[j].first << " ";
//        for (int j = 0; j < cnt_landmarks; ++j)
//            if (dist_to_start_from_lm[j].second == lm)
//                std::cout << dist_to_start_from_lm[j].first << " ";
//        std::cout << "\n";
//    }
//    std::cout << "\n";

}

void CH::LandMarks::build_min_ways(const CH::Graph &graph) {
    for (int lm = 0; lm < cnt_landmarks; ++lm) {
        min_dist_for_landmarks[lm] = dijkstra_min_all_vertices(landmarks[lm], graph);
        std::cout << "build min dist for " << lm << " landmarks" << "\n";
    }
    //    std::iota(this->active_landmarks.begin(), this->active_landmarks.end(), 0);
    std::cout << "builded min ways\n";
}
