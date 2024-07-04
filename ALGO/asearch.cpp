//
// Created by apple on 03.07.2024.
//

#include "asearch.h"
#include <set>
#include <vector>

CH::weight_t
a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, const std::vector<CH::weight_t> &p,
         double *percent) {
    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    std::vector<CH::weight_t> k(graph.n, std::numeric_limits<CH::weight_t>::max());
    k[start] = p[start];

    distances[start] = 0;

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({k[start], start});


    int count_viewed_vertex = 0;
    std::vector<size_t> min_way(graph.n, -1);
    min_way[start] = start;


    CH::weight_t result = std::numeric_limits<CH::weight_t>::max();

    while (!active_vertices.empty()) {
//        CH::weight_t current_distance = active_vertices.begin()->first;

        //------------------------------------------------------------------------------------------------
        count_viewed_vertex++;
        //------------------------------------------------------------------------------------------------


        CH::vertex_t current_node = active_vertices.begin()->second;

        if (current_node == finish) {
            result = distances[finish];
            break;
        }

        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            distances[edge.to] = std::min(distances[edge.to], distances[current_node] + edge.weight);

            CH::weight_t new_k_distance = distances[current_node] + edge.weight + p[edge.to];

            if (new_k_distance < k[edge.to]) {
                active_vertices.erase({k[edge.to], edge.to});
                k[edge.to] = new_k_distance;
                active_vertices.insert({new_k_distance, edge.to});

                //------------------------------------------------------------------------------------------------
                min_way[edge.to] = current_node;
                //------------------------------------------------------------------------------------------------

            }
        }
    }

    if (percent != nullptr) {
        if (result == std::numeric_limits<CH::weight_t>::max()) *percent = 0;
        else {
            int len_way = 0;
            CH::vertex_t curr = finish;
            while (curr != start) {
                len_way++;
                curr = min_way[curr];
            }
            *percent = 100 * len_way / (double) count_viewed_vertex;
        }
    }


    return result;
}

CH::weight_t
B_a_search(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, const std::vector<CH::weight_t> &p_s,
           const std::vector<CH::weight_t> &p_f,
           double *percent) {
    std::vector<CH::weight_t> distances_start(graph.n, std::numeric_limits<CH::weight_t>::max());
    std::vector<CH::weight_t> k_s(graph.n, std::numeric_limits<CH::weight_t>::max());
    k_s[start] = p_s[start];
    distances_start[start] = 0;
    std::vector<bool> mark_from_start(graph.n, false);
    mark_from_start[start] = true;

    std::vector<CH::weight_t> distances_finish(graph.n, std::numeric_limits<CH::weight_t>::max());
    std::vector<CH::weight_t> k_f(graph.n, std::numeric_limits<CH::weight_t>::max());
    k_f[finish] = p_f[finish];
    distances_finish[finish] = 0;
    std::vector<bool> mark_from_finish(graph.n, false);
    mark_from_finish[finish] = true;

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_start;
    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_finish;


    active_vertices_start.insert({k_s[start], start});
    active_vertices_finish.insert({k_f[finish], finish});

    size_t selector = 0;

    int count_viewed_vertex = 0;
    std::vector<size_t> min_way_s(graph.n, -1), min_way_f(graph.n, -1);
    min_way_s[start] = start;
    min_way_f[finish] = finish;

    CH::weight_t result = std::numeric_limits<CH::weight_t>::max();
    CH::vertex_t middle_vertex;


    while (!active_vertices_start.empty() && !active_vertices_finish.empty()) {
        std::set<std::pair<CH::weight_t, CH::vertex_t>> *active_vertices = nullptr;
        std::vector<CH::weight_t> *k = nullptr;
        const std::vector<CH::weight_t> *p = nullptr;
        std::vector<CH::weight_t> *distances = nullptr;
        std::vector<bool> *mark_from_ = nullptr;
        std::vector<size_t>* min_way_ = nullptr;

        count_viewed_vertex++;


        if (selector == 0) {
            active_vertices = &active_vertices_start;
            distances = &distances_start;
            mark_from_ = &mark_from_start;
            k = &k_s;
            p = &p_s;
            min_way_ = &min_way_s;
        } else {
            active_vertices = &active_vertices_finish;
            distances = &distances_finish;
            mark_from_ = &mark_from_finish;
            k = &k_f;
            p = &p_f;
            min_way_ = &min_way_f;
        }


        CH::weight_t current_distance = active_vertices->begin()->first;
        CH::vertex_t current_node = active_vertices->begin()->second;
        active_vertices->erase(active_vertices->begin());
        (*mark_from_)[current_node] = true;

        if (mark_from_finish[current_node] && mark_from_start[current_node]) {
            result = std::min(result, distances_start[current_node] + distances_finish[current_node]);
            middle_vertex = current_node;
        }

        if (current_distance > result) continue;

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = (*distances)[current_node] + edge.weight + (*p)[edge.to];

            (*distances)[edge.to] = std::min((*distances)[edge.to], (*distances)[current_node] + edge.weight);

            if (new_distance < (*k)[edge.to]) {
                active_vertices->erase({(*k)[edge.to], edge.to});
                (*k)[edge.to] = new_distance;
                active_vertices->insert({new_distance, edge.to});

                (*min_way_)[edge.to] = current_node;
            }
        }


        selector = (selector + 1) % 2;
    }

    if (percent != nullptr) {
        if (result == std::numeric_limits<CH::weight_t>::max()) *percent = 0;
        else {
            int len_way = 0;
            CH::vertex_t curr = middle_vertex;
            while (curr != start) {
                len_way++;
                curr = min_way_s[curr];
            }

            curr = middle_vertex;
            while (curr != finish) {
                len_way++;
                curr = min_way_f[curr];
            }
            *percent = 100 * len_way / (double) count_viewed_vertex;
        }
    }


    return result;
}
