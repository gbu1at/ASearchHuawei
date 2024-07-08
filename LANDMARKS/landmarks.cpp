//
// Created by apple on 04.07.2024.
//

#include "landmarks.h"
#include <random>
#include "../ALGO/dijkstra.h"
#include <cassert>
//#include <deque>
#include <set>
#include <iostream>


CH::vertex_t generate_new_landmark(const CH::Graph &graph, const std::vector<CH::vertex_t>& landmarks) {
    std::vector<CH::weight_t> dist(graph.n, -1);


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertex;

    for (auto v : landmarks) {
        dist[v] = 0;
        active_vertex.insert({0, v});
    }

    while (!active_vertex.empty()) {
        auto[d, v] = *active_vertex.begin();
        active_vertex.erase(active_vertex.begin());

        for (auto e : graph.vertices[v].adj) {
            if (dist[e.to] > dist[v] + e.weight) {
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
    return new_landmark;
}

void CH::LandMarks::random_landmarks(size_t cnt_landmarks, const CH::Graph &graph) {
    this->init_landmarks(cnt_landmarks);

    std::iota(landmarks.begin(), landmarks.end(), 0);
    Setting::shuffle(landmarks.begin(), landmarks.end());
    landmarks.resize(cnt_landmarks);

    this->build_min_ways(graph);
}

void CH::LandMarks::smart_landmarks(size_t cnt_landmarks, const CH::Graph &graph) {
    this->init_landmarks(cnt_landmarks);
    std::vector<CH::vertex_t > lm_ = {(CH::vertex_t)(Setting::PROJECT_RND() % graph.n)};
    std::vector<CH::vertex_t > lm = {generate_new_landmark(graph, lm_)};


    for (int i = 1; i < cnt_landmarks; ++i) {
        CH::vertex_t v = generate_new_landmark(graph, lm);
        lm.push_back(v);
        std::cout << v << "\t";
    }
    std::cout << "\n";
    landmarks = lm;

    std::cout << "found smart lm\n";

    this->build_min_ways(graph);
}

CH::weight_t CH::LandMarks::get_dist(CH::vertex_t v) {

    assert(finish != -1);

    auto result = std::numeric_limits<weight_t>::min();
    for (int lm = 0; lm < cnt_landmarks; ++lm)
        result = std::max(result, abs(min_dist_for_landmarks[lm][finish] -
                                      min_dist_for_landmarks[lm][v]));
    return result;
}


void CH::LandMarks::init_landmarks(int cnt_landmarks) {
    this->cnt_landmarks = cnt_landmarks;
    landmarks.assign(cnt_landmarks, -1);
    min_dist_for_landmarks.assign(cnt_landmarks, {});
}


void CH::LandMarks::set_finish(CH::vertex_t finish) {
    CH::LandMarks::finish = finish;
}

void CH::LandMarks::build_min_ways(const CH::Graph& graph) {
    for (int lm = 0; lm < cnt_landmarks; ++lm)
        min_dist_for_landmarks[lm] = dijkstra_min_all_vertices(landmarks[lm], graph);
    std::cout << "builded min ways\n";
}
