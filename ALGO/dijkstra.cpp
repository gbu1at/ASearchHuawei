//
// Created by apple on 02.07.2024.
//

#include "dijkstra.h"
#include <vector>
#include <set>

std::vector<CH::weight_t> dijkstra_min_all_vertices(CH::vertex_t start, const CH::Graph &graph) {
    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    distances[start] = 0;


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({0, start});

    while (!active_vertices.empty()) {
        CH::weight_t current_distance = active_vertices.begin()->first;
        CH::vertex_t current_node = active_vertices.begin()->second;
        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if (new_distance < distances[edge.to]) {
                active_vertices.erase({distances[edge.to], edge.to});
                distances[edge.to] = new_distance;
                active_vertices.insert({new_distance, edge.to});
            }
        }
    }
    return distances;
}

CH::weight_t dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph) {
    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    distances[start] = 0;


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({0, start});

    while (!active_vertices.empty()) {
        CH::weight_t current_distance = active_vertices.begin()->first;
        CH::vertex_t current_node = active_vertices.begin()->second;

        if (current_node == finish) return distances[current_node];

        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if (new_distance < distances[edge.to]) {
                active_vertices.erase({distances[edge.to], edge.to});
                distances[edge.to] = new_distance;
                active_vertices.insert({new_distance, edge.to});
            }
        }
    }
    return std::numeric_limits<CH::weight_t>::max();
}

CH::weight_t B_dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph) {
    std::vector<CH::weight_t> distances_start(graph.n, std::numeric_limits<CH::weight_t>::max());
    distances_start[start] = 0;
    std::vector<bool> mark_from_start(graph.n, false);
    mark_from_start[start] = true;

    std::vector<CH::weight_t> distances_finish(graph.n, std::numeric_limits<CH::weight_t>::max());
    distances_finish[start] = 0;
    std::vector<bool> mark_from_finish(graph.n, false);
    mark_from_finish[finish] = true;

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_start;
    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_finish;


    active_vertices_start.insert({0, start});
    active_vertices_finish.insert({0, finish});

    size_t selector = 0;

    while (!active_vertices_start.empty() && !active_vertices_finish.empty()) {
        std::set<std::pair<CH::weight_t, CH::vertex_t>> *active_vertices = nullptr;
        std::vector<CH::weight_t> *distances = nullptr;
        std::vector<bool> *mark_from_ = nullptr;


        if (selector == 0) {
            active_vertices = &active_vertices_start;
            distances = &distances_start;
            mark_from_ = &mark_from_start;

        } else {
            active_vertices = &active_vertices_finish;
            distances = &distances_finish;
            mark_from_ = &mark_from_finish;

        }


        CH::weight_t current_distance = active_vertices->begin()->first;
        CH::vertex_t current_node = active_vertices->begin()->second;
        active_vertices->erase(active_vertices->begin());
        (*mark_from_)[current_node] = true;

        if (mark_from_finish[current_node] && mark_from_start[current_node])
            return distances_start[current_node] + distances_finish[current_node];


        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if (new_distance < (*distances)[edge.to]) {
                active_vertices->erase({(*distances)[edge.to], edge.to});
                (*distances)[edge.to] = new_distance;
                active_vertices->insert({new_distance, edge.to});
            }
        }


        selector = (selector + 1) % 2;
    }
    return std::numeric_limits<CH::weight_t>::max();
}
