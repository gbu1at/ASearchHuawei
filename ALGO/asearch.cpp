//
// Created by apple on 03.07.2024.
//

#include "asearch.h"
#include <set>
#include <vector>

CH::weight_t
a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, const std::vector<CH::weight_t> &p) {
    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    std::vector<CH::weight_t> k(graph.n, std::numeric_limits<CH::weight_t>::max()); k[start] = p[start];

    distances[start] = 0;

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({k[start], start});

    while (!active_vertices.empty()) {
//        CH::weight_t current_distance = active_vertices.begin()->first;
        CH::vertex_t current_node = active_vertices.begin()->second;

        if (current_node == finish) return distances[finish];

        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            distances[edge.to] = std::min(distances[edge.to], distances[current_node] + edge.weight);

            CH::weight_t new_k_distance = distances[current_node] + edge.weight + p[edge.to];

            if (new_k_distance < k[edge.to]) {
                active_vertices.erase({k[edge.to], edge.to});
                k[edge.to] = new_k_distance;
                active_vertices.insert({new_k_distance, edge.to});
            }
        }
    }
    return std::numeric_limits<CH::weight_t>::max();
}

CH::weight_t
B_a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, const std::vector<CH::weight_t> &p_s,
           const std::vector<CH::weight_t> &p_f) {
    std::vector<CH::weight_t> distances_start(graph.n, std::numeric_limits<CH::weight_t>::max());
    std::vector<CH::weight_t> k_s(graph.n, std::numeric_limits<CH::weight_t>::max()); k_s[start] = p_s[start];
    distances_start[start] = 0;
    std::vector<bool> mark_from_start(graph.n, false);
    mark_from_start[start] = true;

    std::vector<CH::weight_t> distances_finish(graph.n, std::numeric_limits<CH::weight_t>::max());
    std::vector<CH::weight_t> k_f(graph.n, std::numeric_limits<CH::weight_t>::max()); k_f[finish] = p_f[finish];
    distances_finish[finish] = 0;
    std::vector<bool> mark_from_finish(graph.n, false);
    mark_from_finish[finish] = true;

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_start;
    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_finish;

    CH::weight_t result = std::numeric_limits<CH::weight_t>::max();

    active_vertices_start.insert({k_s[start], start});
    active_vertices_finish.insert({k_f[finish], finish});

    size_t selector = 0;

    while (!active_vertices_start.empty() && !active_vertices_finish.empty()) {
        std::set<std::pair<CH::weight_t, CH::vertex_t>> *active_vertices = nullptr;
        std::vector<CH::weight_t>* k = nullptr;
        const std::vector<CH::weight_t>* p = nullptr;
        std::vector<CH::weight_t> *distances = nullptr;
        std::vector<bool> *mark_from_ = nullptr;


        if (selector == 0) {
            active_vertices = &active_vertices_start;
            distances = &distances_start;
            mark_from_ = &mark_from_start;
            k = &k_s;
            p = &p_s;
        } else {
            active_vertices = &active_vertices_finish;
            distances = &distances_finish;
            mark_from_ = &mark_from_finish;
            k = &k_f;
            p = &p_f;
        }


        CH::weight_t current_distance = active_vertices->begin()->first;
        CH::vertex_t current_node = active_vertices->begin()->second;
        active_vertices->erase(active_vertices->begin());
        (*mark_from_)[current_node] = true;

        if (mark_from_finish[current_node] && mark_from_start[current_node])
            result = std::min(result, distances_start[current_node] + distances_finish[current_node]);

        if (current_distance > result) continue;

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = (*distances)[current_node] + edge.weight + (*p)[edge.to];

            if (new_distance < (*k)[edge.to]) {
                active_vertices->erase({(*k)[edge.to], edge.to});
                (*k)[edge.to] = new_distance;
                active_vertices->insert({new_distance, edge.to});
            }
        }


        selector = (selector + 1) % 2;
    }
    return result;
}
