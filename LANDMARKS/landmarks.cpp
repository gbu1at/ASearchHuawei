//
// Created by apple on 04.07.2024.
//

#include "landmarks.h"
#include <random>
#include "../ALGO/dijkstra.h"
#include <cassert>
#include <deque>



int generate_new_landmark(const CH::Graph &graph, const std::vector<CH::vertex_t>& landmarks) {
    std::vector<CH::weight_t> dist(graph.n, -1);


    std::deque<std::pair<CH::weight_t, CH::vertex_t>> active_vertex;

    for (auto v : landmarks) {
        dist[v] = 0;
        active_vertex.emplace_back(0, v);
    }

    while (!active_vertex.empty()) {
        auto[d, v] = active_vertex.front();
        active_vertex.pop_front();

        for (auto e : graph.vertices[v].adj) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[v] + 1;
                active_vertex.emplace_back(dist[e.to], e.to);
            }
        }
    }
    int new_landmark = landmarks[0];
    for (int v = 0; v < graph.n; ++v)
        if (dist[v] > dist[new_landmark])
            new_landmark = v;
    return new_landmark;
}

void CH::LandMarks::random_landmarks(size_t cnt, const CH::Graph &graph) {
    this->init_landmarks(cnt);

    std::iota(landmarks.begin(), landmarks.end(), 0);
    RandomUtil::shuffle(landmarks.begin(), landmarks.end());
    landmarks.resize(cnt);

    this->build_min_ways(graph);
}

void CH::LandMarks::smart_landmarks(size_t cnt, const CH::Graph &graph) {
    this->init_landmarks(cnt);
    std::vector<CH::vertex_t > lm = {(CH::vertex_t)(RandomUtil::PROJECT_RND() % graph.n)};

    for (int i = 1; i < cnt; ++i)
        lm.push_back(generate_new_landmark(graph, lm));
    landmarks = lm;
}

CH::weight_t CH::LandMarks::get_dist(CH::vertex_t v) {

    assert(finish != -1);

    auto result = std::numeric_limits<weight_t>::min();
    for (int lm = 0; lm < cnt; ++lm)
        result = std::max(result, abs(min_dist_for_landmarks[lm][finish] -
                                      min_dist_for_landmarks[lm][v]));
    return result;
}


void CH::LandMarks::init_landmarks(int cnt) {
    this->cnt = cnt;
    landmarks.assign(cnt, -1);
    min_dist_for_landmarks.assign(cnt, {});
}


void CH::LandMarks::set_finish(CH::vertex_t finish) {
    CH::LandMarks::finish = finish;
}

void CH::LandMarks::build_min_ways(const CH::Graph& graph) {
    for (int lm = 0; lm < cnt; ++lm)
        min_dist_for_landmarks[lm] = dijkstra_min_all_vertices(landmarks[lm], graph);
}
