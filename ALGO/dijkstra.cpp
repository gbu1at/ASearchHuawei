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

CH::weight_t
dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, double *percent) {
    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    distances[start] = 0;


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({0, start});


    int count_viewed_vertex = 0;
    std::vector<size_t> min_way(graph.n, -1);
    min_way[start] = start;


    CH::weight_t result = std::numeric_limits<CH::weight_t>::max();

    while (!active_vertices.empty()) {
        //------------------------------------------------------------------------------------------------
        count_viewed_vertex++;
        //------------------------------------------------------------------------------------------------


        CH::weight_t current_distance = active_vertices.begin()->first;
        CH::vertex_t current_node = active_vertices.begin()->second;

        if (current_node == finish) {
            result = distances[current_node];
        }

        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if (new_distance < distances[edge.to]) {
                active_vertices.erase({distances[edge.to], edge.to});
                distances[edge.to] = new_distance;
                active_vertices.insert({new_distance, edge.to});

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

CH::weight_t B_dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph& graph, double* percent) {
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



    int count_viewed_vertex = 0;
    std::vector<size_t> min_way_s(graph.n, -1), min_way_f(graph.n, -1);
    min_way_s[start] = start;
    min_way_f[finish] = finish;

    CH::weight_t result = std::numeric_limits<CH::weight_t>::max();
    CH::vertex_t middle_vertex;



    while (!active_vertices_start.empty() && !active_vertices_finish.empty()) {
        std::set<std::pair<CH::weight_t, CH::vertex_t>> *active_vertices = nullptr;
        std::vector<CH::weight_t> *distances = nullptr;
        std::vector<bool> *mark_from_ = nullptr;
        std::vector<size_t> *min_way_ = nullptr;



        if (selector == 0) {
            active_vertices = &active_vertices_start;
            distances = &distances_start;
            mark_from_ = &mark_from_start;
            min_way_ = &min_way_s;

        } else {
            active_vertices = &active_vertices_finish;
            distances = &distances_finish;
            mark_from_ = &mark_from_finish;
            min_way_ = &min_way_f;

        }


        count_viewed_vertex++;


        CH::weight_t current_distance = active_vertices->begin()->first;
        CH::vertex_t current_node = active_vertices->begin()->second;
        active_vertices->erase(active_vertices->begin());
        (*mark_from_)[current_node] = true;

        if (mark_from_finish[current_node] && mark_from_start[current_node]) {
            middle_vertex = current_node;
            result = distances_start[current_node] + distances_finish[current_node];
            break;
        }


        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if (new_distance < (*distances)[edge.to]) {
                active_vertices->erase({(*distances)[edge.to], edge.to});
                (*distances)[edge.to] = new_distance;
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
