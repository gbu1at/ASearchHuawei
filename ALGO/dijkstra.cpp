//
// Created by apple on 02.07.2024.
//

#include "dijkstra.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <queue>
#include <assert.h>

std::vector<std::pair<CH::weight_t, int>> Dijkstra::distances;
std::vector<std::pair<size_t, int>> Dijkstra::min_way;
int Dijkstra::T;

void Dijkstra::init(const CH::Graph &graph) {
    Dijkstra::T = 0;
    Dijkstra::distances.assign(graph.n, {INF_WEIGHT, T});
    Dijkstra::min_way.assign(graph.n, {-1, T});
}


std::vector<CH::weight_t> dijkstra_min_all_vertices(CH::vertex_t start, const CH::Graph &graph) {
    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    distances[start] = 0;


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({0, start});

//    int time1 = clock();
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
//    int time2 = clock();
//
//    std::cout << (time2 - time1) / (double) CLOCKS_PER_SEC << "\n";
    return distances;
}

CH::weight_t
Dijkstra::dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, double *percent,
                                    int *cnt_move, int *cnt_edge_in_way_, std::vector<CH::vertex_t>* vertex_min_way) {

    Dijkstra::T++;
//    std::vector<CH::weight_t> distances(graph.n, std::numeric_limits<CH::weight_t>::max());
    Dijkstra::distances[start] = {0, Dijkstra::T};


    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({0, start});


    int count_viewed_vertex = 0;
    Dijkstra::min_way[start] = {start, Dijkstra::T};


    CH::weight_t result = std::numeric_limits<CH::weight_t>::max();

//    int time1 = clock();
    while (!active_vertices.empty()) {
        //------------------------------------------------------------------------------------------------
        count_viewed_vertex++;
        //------------------------------------------------------------------------------------------------


        CH::weight_t current_distance = active_vertices.begin()->first;
        CH::vertex_t current_node = active_vertices.begin()->second;

        if (current_node == finish) {
            result = Dijkstra::distances[current_node].first;
            break;
        }

        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if (Dijkstra::distances[edge.to].second != Dijkstra::T)
                Dijkstra::distances[edge.to] = {INF_WEIGHT, Dijkstra::T};

            if (new_distance < Dijkstra::distances[edge.to].first) {
                active_vertices.erase({Dijkstra::distances[edge.to].first, edge.to});
                Dijkstra::distances[edge.to].first = new_distance;
                active_vertices.insert({new_distance, edge.to});

                //------------------------------------------------------------------------------------------------
                Dijkstra::min_way[edge.to] = {current_node, Dijkstra::T};
                //------------------------------------------------------------------------------------------------
            }
        }
    }
//    int time2 = clock();
//
//    std::cout << (time2 - time1) / (double) CLOCKS_PER_SEC << "\n";

    int cnt_edge_in_way = 0;
    if (result != std::numeric_limits<CH::weight_t>::max()) {
        CH::vertex_t curr = finish;
        if (vertex_min_way != nullptr) (*vertex_min_way).push_back(curr);
        while (curr != start) {
            cnt_edge_in_way++;
            curr = min_way[curr].first;
            if (vertex_min_way != nullptr) (*vertex_min_way).push_back(curr);
        }
    }


    if (percent != nullptr) {
        if (result == std::numeric_limits<CH::weight_t>::max()) *percent = 0;
        else *percent = 100 * cnt_edge_in_way / (double) count_viewed_vertex;
    }

    if (cnt_move != nullptr)
        *cnt_move = count_viewed_vertex;

    if (cnt_edge_in_way_ != nullptr)
        *cnt_edge_in_way_ = cnt_edge_in_way;

    return result;
}

int BDijkstra::T;
std::vector<std::pair<CH::weight_t, int>> BDijkstra::distances_start;
std::vector<std::pair<CH::weight_t, int>> BDijkstra::distances_finish;
std::vector<std::pair<bool, int>> BDijkstra::mark_from_start;
std::vector<std::pair<bool, int>> BDijkstra::mark_from_finish;
std::vector<std::pair<size_t, int>> BDijkstra::min_way_s;
std::vector<std::pair<size_t, int>> BDijkstra::min_way_f;

void BDijkstra::init(const CH::Graph &graph) {
    BDijkstra::T = 0;
    BDijkstra::distances_start.assign(graph.n, {INF_WEIGHT, T});
    BDijkstra::distances_finish.assign(graph.n, {INF_WEIGHT, T});
    BDijkstra::mark_from_start.assign(graph.n, {INF_WEIGHT, T});
    BDijkstra::mark_from_finish.assign(graph.n, {INF_WEIGHT, T});
    BDijkstra::min_way_s.assign(graph.n, {-1, T});
    BDijkstra::min_way_f.assign(graph.n, {-1, T});
}

CH::weight_t
BDijkstra::B_dijkstra_min_two_vertices(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, double *percent,
                                       int *cnt_move, int *cnt_edge_in_way_) {
    BDijkstra::T++;
    BDijkstra::distances_start[start] = {0, BDijkstra::T};
    BDijkstra::mark_from_start[start] = {true, BDijkstra::T};

    BDijkstra::distances_finish[finish] = {0, BDijkstra::T};
    BDijkstra::mark_from_finish[finish] = {true, BDijkstra::T};

    std::priority_queue<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_start;
    std::priority_queue<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_finish;


    active_vertices_start.emplace(0, start);
    active_vertices_finish.emplace(0, finish);

    size_t selector = 0;


    int count_viewed_vertex = 0;
    BDijkstra::min_way_s[start] = {start, BDijkstra::T};
    BDijkstra::min_way_f[finish] = {finish, BDijkstra::T};

    CH::weight_t result = INF_WEIGHT;
    CH::vertex_t middle_vertex;

    while (!active_vertices_start.empty() && !active_vertices_finish.empty()) {
        std::priority_queue<std::pair<CH::weight_t, CH::vertex_t>> *active_vertices = nullptr;
        std::vector<std::pair<CH::weight_t, int>> *distances_from_ = nullptr;
        std::vector<std::pair<CH::weight_t, int>> *distances_to_ = nullptr;
        std::vector<std::pair<bool, int>> *mark_from_ = nullptr;
        std::vector<std::pair<bool, int>> *mark_to_ = nullptr;
        std::vector<std::pair<size_t, int>> *min_way_ = nullptr;


        if (selector == 0) {
            active_vertices = &active_vertices_start;
            distances_from_ = &BDijkstra::distances_start;
            distances_to_ = &BDijkstra::distances_finish;
            mark_from_ = &BDijkstra::mark_from_start;
            mark_to_ = &BDijkstra::mark_from_finish;
            min_way_ = &BDijkstra::min_way_s;

        } else {
            active_vertices = &active_vertices_finish;
            distances_from_ = &BDijkstra::distances_finish;
            distances_to_ = &BDijkstra::distances_start;
            mark_from_ = &BDijkstra::mark_from_finish;
            mark_to_ = &BDijkstra::mark_from_start;
            min_way_ = &BDijkstra::min_way_f;
        }
        selector = (selector + 1) % 2;


        CH::weight_t current_distance = -active_vertices->top().first;
        CH::vertex_t current_node = active_vertices->top().second;
        active_vertices->pop();

        if (current_distance > (*distances_from_)[current_node].first) continue;

        count_viewed_vertex++;


        (*mark_from_)[current_node] = {true, BDijkstra::T};

        for (const CH::Edge &edge: graph.vertices[current_node].adj) {
            CH::weight_t new_distance = current_distance + edge.weight;

            if ((*distances_from_)[edge.to].second != BDijkstra::T)
                (*distances_from_)[edge.to] = {INF_WEIGHT, BDijkstra::T};

            if (new_distance < (*distances_from_)[edge.to].first) {
//                active_vertices->erase({(*distances_from_)[edge.to].first, edge.to});
                (*distances_from_)[edge.to].first = new_distance;
                active_vertices->emplace(-new_distance, edge.to);
                (*min_way_)[edge.to] = {current_node, BDijkstra::T};
            }
            if ((*mark_to_)[edge.to].second != BDijkstra::T)
                (*mark_to_)[edge.to] = {false, BDijkstra::T};

            if ((*mark_to_)[edge.to].first &&
                result > (*distances_from_)[current_node].first + edge.weight + (*distances_to_)[edge.to].first) {
                result = (*distances_from_)[current_node].first + edge.weight + (*distances_to_)[edge.to].first;
                middle_vertex = edge.to;
            }
        }

        if (BDijkstra::mark_from_finish[current_node].second != BDijkstra::T)
            BDijkstra::mark_from_finish[current_node] = {false, BDijkstra::T};

        if (BDijkstra::mark_from_start[current_node].second != BDijkstra::T)
            BDijkstra::mark_from_start[current_node] = {false, BDijkstra::T};

        if (BDijkstra::mark_from_finish[current_node].first && BDijkstra::mark_from_start[current_node].first) {
            if (result >
                BDijkstra::distances_start[current_node].first + BDijkstra::distances_finish[current_node].first) {
                result = BDijkstra::distances_start[current_node].first +
                         BDijkstra::distances_finish[current_node].first;
                middle_vertex = current_node;
            }
            break;
        }
    }

    int cnt_edge_in_way = 0;
    if (result != std::numeric_limits<CH::weight_t>::max()) {
        CH::vertex_t curr = middle_vertex;
        while (curr != start) {
            cnt_edge_in_way++;
            curr = BDijkstra::min_way_s[curr].first;
        }

        curr = middle_vertex;
        while (curr != finish) {
            cnt_edge_in_way++;
            curr = BDijkstra::min_way_f[curr].first;
        }
    }

    if (percent != nullptr) {
        if (result == std::numeric_limits<CH::weight_t>::max()) *percent = 0;
        else *percent = 100 * cnt_edge_in_way / (double) count_viewed_vertex;
    }

    if (cnt_move != nullptr)
        *cnt_move = count_viewed_vertex;

    if (cnt_edge_in_way_ != nullptr)
        *cnt_edge_in_way_ = cnt_edge_in_way;

    if (Setting::is_debug()) {
        CH::weight_t res = Dijkstra::dijkstra_min_two_vertices(start, finish, graph);
        assert(res == result);
    }


    return result;
}
