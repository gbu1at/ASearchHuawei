//
// Created by apple on 03.07.2024.
//

#include "asearch.h"
#include <set>
#include <vector>
#include <iostream>
#include <cassert>
#include "dijkstra.h"

const CH::Graph *ASearch::graph;
std::vector<std::pair<CH::weight_t, int>> ASearch::distances;
std::vector<std::pair<bool, int>> ASearch::mark;
std::vector<std::pair<size_t, int>> ASearch::min_way;
std::vector<std::pair<CH::weight_t, int>> ASearch::k;
int ASearch::T;

void ASearch::init(const CH::Graph &g) {
    ASearch::graph = &g;
    ASearch::T = 0;
    ASearch::distances.assign(g.n, {INF_WEIGHT, T});
    ASearch::mark.assign(g.n, {false, T});
    ASearch::min_way.assign(g.n, {-1, T});
    ASearch::k.assign(g.n, {INF_WEIGHT, T});
}


CH::weight_t
ASearch::a_search(CH::vertex_t start, CH::vertex_t finish,
                  std::function<CH::weight_t(CH::vertex_t)> p,
                  double *percent, std::vector<bool> *mark_, int *cnt_move_, int *cnt_edge_in_way_) {
    int time1 = clock();

    ASearch::k[start] = {p(start), ASearch::T};

    ASearch::T++;

    ASearch::distances[start] = {0, ASearch::T};

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices;

    active_vertices.insert({ASearch::k[start].first, start});


    int count_viewed_vertex = 0;
    ASearch::min_way[start] = {start, ASearch::T};


    CH::weight_t result = INF_WEIGHT;

    int time2 = clock();
    while (!active_vertices.empty()) {
//        CH::weight_t current_distance = active_vertices.begin()->first;

        //------------------------------------------------------------------------------------------------
        count_viewed_vertex++;
        //------------------------------------------------------------------------------------------------


        CH::vertex_t current_node = active_vertices.begin()->second;


//        std::cout << current_node << "\n";


        ASearch::mark[current_node] = {true, ASearch::T};

        if (current_node == finish) {
            result = ASearch::distances[finish].first;
            break;
        }

        active_vertices.erase(active_vertices.begin());

        for (const CH::Edge &edge: graph->vertices[current_node].adj) {
            if (ASearch::distances[edge.to].second != ASearch::T)
                ASearch::distances[edge.to] = {INF_WEIGHT, ASearch::T};

            ASearch::distances[edge.to].first = std::min(ASearch::distances[edge.to].first,
                                                         ASearch::distances[current_node].first + edge.weight);

            ASearch::distances[edge.to].second = ASearch::T;

            CH::weight_t new_k_distance = ASearch::distances[current_node].first + edge.weight + p(edge.to);

            if (ASearch::k[edge.to].second != ASearch::T)
                ASearch::k[edge.to] = {INF_WEIGHT, ASearch::T};

            if (new_k_distance < ASearch::k[edge.to].first) {
                active_vertices.erase({ASearch::k[edge.to].first, edge.to});
                ASearch::k[edge.to].first = new_k_distance;
                active_vertices.insert({new_k_distance, edge.to});

                //------------------------------------------------------------------------------------------------
                ASearch::min_way[edge.to] = {current_node, ASearch::T};
                //------------------------------------------------------------------------------------------------

            }
        }
    }

    int time3 = clock();
    std::cout << (time3 - time2) / (double) CLOCKS_PER_SEC << "\n";

    int cnt_edge_in_way = 0;
    if (result != std::numeric_limits<CH::weight_t>::max()) {
        CH::vertex_t curr = finish;
        while (curr != start) {
            cnt_edge_in_way++;
            curr = ASearch::min_way[curr].first;
        }
    }
    if (percent != nullptr) {
        if (result == std::numeric_limits<CH::weight_t>::max()) *percent = 0;
        else {

            *percent = 100 * cnt_edge_in_way / (double) count_viewed_vertex;
        }
    }

    if (mark_ != nullptr) {
        mark_->assign(ASearch::graph->n, false);
        for (int i = 0; i < ASearch::graph->n; ++i)
            (*mark_)[i] = ASearch::mark[i].first;
    }

    if (cnt_move_ != nullptr)
        *cnt_move_ = count_viewed_vertex;

    if (cnt_edge_in_way_ != nullptr)
        *cnt_edge_in_way_ = cnt_edge_in_way;

    if (Setting::is_debug()) {
        CH::weight_t res = dijkstra_min_two_vertices(start, finish, *graph);
        assert(result == res);
    }

    int time4 = clock();
    std::cout << (time4 - time1) / (double) CLOCKS_PER_SEC << "\n";
    return result;
}


void BASearch::init(const CH::Graph &graph) {
    BASearch::graph = &graph;
    BASearch::T = 0;
    BASearch::distances_start.assign(graph.n, {INF_WEIGHT, T});
    BASearch::distances_finish.assign(graph.n, {INF_WEIGHT, T});
    BASearch::k_s.assign(graph.n, {INF_WEIGHT, T});
    BASearch::k_f.assign(graph.n, {INF_WEIGHT, T});
    BASearch::mark_from_start.assign(graph.n, {false, T});
    BASearch::mark_from_finish.assign(graph.n, {false, T});
    BASearch::min_way_s.assign(graph.n, {-1, T});
    BASearch::min_way_f.assign(graph.n, {-1, T});
    BASearch::mark.assign(graph.n, {false, T});
}

const CH::Graph *BASearch::graph;
int BASearch::T;
std::vector<std::pair<CH::weight_t, int>> BASearch::distances_start;
std::vector<std::pair<CH::weight_t, int>> BASearch::distances_finish;
std::vector<std::pair<CH::weight_t, int>> BASearch::k_s;
std::vector<std::pair<CH::weight_t, int>> BASearch::k_f;
std::vector<std::pair<bool, int>> BASearch::mark_from_start;
std::vector<std::pair<bool, int>> BASearch::mark_from_finish;
std::vector<std::pair<int, int>> BASearch::min_way_s;
std::vector<std::pair<int, int>> BASearch::min_way_f;
std::vector<std::pair<bool, int>> BASearch::mark;

CH::weight_t
BASearch::B_a_search(CH::vertex_t start, CH::vertex_t finish,
                     std::function<CH::weight_t(CH::vertex_t)> p_s,
                     std::function<CH::weight_t(CH::vertex_t)> p_f,
                     double *percent, std::vector<bool> *mark_, int *cnt_move_, int *cnt_edge_in_way_) {
    int time1 = clock();

    BASearch::T++;
    BASearch::k_s[start] = {p_s(start), BASearch::T};
    BASearch::distances_start[start] = {0, BASearch::T};

    BASearch::mark_from_start[start] = {true, BASearch::T};


    BASearch::k_f[finish] = {p_f(finish), BASearch::T};
    BASearch::distances_finish[finish] = {0, BASearch::T};
    BASearch::mark_from_finish[finish] = {true, BASearch::T};

    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_start;
    std::set<std::pair<CH::weight_t, CH::vertex_t>> active_vertices_finish;


    active_vertices_start.insert({BASearch::k_s[start].first, start});
    active_vertices_finish.insert({BASearch::k_f[finish].first, finish});

    size_t selector = 0;

    int count_viewed_vertex = 0;
    BASearch::min_way_s[start] = {start, BASearch::T};
    BASearch::min_way_f[finish] = {finish, BASearch::T};

    CH::weight_t result = INF_WEIGHT;
    CH::vertex_t middle_vertex;

    int time2 = clock();
    while (!active_vertices_start.empty() && !active_vertices_finish.empty()) {
        std::set<std::pair<CH::weight_t, CH::vertex_t>> *active_vertices = nullptr;
        std::vector<std::pair<CH::weight_t, int>> *k = nullptr;
        std::function<CH::weight_t(CH::vertex_t)> *p = nullptr;
        std::vector<std::pair<CH::weight_t, int>> *distances_from_ = nullptr;
        std::vector<std::pair<CH::weight_t, int>> *distances_to_ = nullptr;
        std::vector<std::pair<bool, int>> *mark_from_ = nullptr;
        std::vector<std::pair<bool, int>> *mark_to_ = nullptr;
        std::vector<std::pair<int, int>> *min_way_ = nullptr;

        if (selector == 0) {
            active_vertices = &active_vertices_start;
            distances_from_ = &BASearch::distances_start;
            distances_to_ = &BASearch::distances_finish;
            mark_from_ = &BASearch::mark_from_start;
            mark_to_ = &BASearch::mark_from_finish;
            k = &BASearch::k_s;
            p = &p_s;
            min_way_ = &BASearch::min_way_s;
        } else {
            active_vertices = &active_vertices_finish;
            distances_from_ = &BASearch::distances_finish;
            distances_to_ = &BASearch::distances_start;
            mark_from_ = &BASearch::mark_from_finish;
            mark_to_ = &BASearch::mark_from_start;
            k = &BASearch::k_f;
            p = &p_f;
            min_way_ = &BASearch::min_way_f;
        }
        selector = (selector + 1) % 2;

        CH::weight_t current_distance = active_vertices->begin()->first;
        CH::vertex_t current_node = active_vertices->begin()->second;
        active_vertices->erase(active_vertices->begin());
        (*mark_from_)[current_node] = {true, BASearch::T};


        if (current_distance >= result)
            break;

        BASearch::mark[current_node] = {true, BASearch::T};

        if ((*mark_to_)[current_node].second != BASearch::T)
            (*mark_to_)[current_node] = {false, BASearch::T};

        if ((*mark_to_)[current_node].first) {
            if (result > (*distances_from_)[current_node].first + (*distances_to_)[current_node].first) {
                result = (*distances_from_)[current_node].first + (*distances_to_)[current_node].first;
                middle_vertex = current_node;
            }
            continue;
        }

        count_viewed_vertex++;

        for (const CH::Edge &edge: BASearch::graph->vertices[current_node].adj) {
            CH::weight_t new_distance = (*distances_from_)[current_node].first + edge.weight + (*p)(edge.to);

            if ((*distances_from_)[edge.to].second != BASearch::T)
                (*distances_from_)[edge.to] = {INF_WEIGHT, BASearch::T};

            (*distances_from_)[edge.to].first = std::min((*distances_from_)[edge.to].first,
                                                         (*distances_from_)[current_node].first + edge.weight);

            if ((*k)[edge.to].second != BASearch::T)
                (*k)[edge.to] = {INF_WEIGHT, BASearch::T};

            if (new_distance < (*k)[edge.to].first) {
                active_vertices->erase({(*k)[edge.to].first, edge.to});
                (*k)[edge.to].first = new_distance;
                active_vertices->insert({new_distance, edge.to});

                (*min_way_)[edge.to].first = current_node;
            }

            if ((*mark_to_)[edge.to].second != BASearch::T)
                (*mark_to_)[edge.to] = {false, BASearch::T};

            if ((*mark_to_)[edge.to].first &&
                result > (*distances_from_)[current_node].first + edge.weight + (*distances_to_)[edge.to].first) {
                result = (*distances_from_)[current_node].first + edge.weight + (*distances_to_)[edge.to].first;
                middle_vertex = edge.to;
            }
        }
    }
    int time3 = clock();

    std::cout << (time3 - time2) / (double) CLOCKS_PER_SEC << "\n";

    int cnt_edge_in_way = 0;
    if (result != std::numeric_limits<CH::weight_t>::max()) {
        CH::vertex_t curr = middle_vertex;
        while (curr != start) {
            cnt_edge_in_way++;
            curr = BASearch::min_way_s[curr].first;
        }

        curr = middle_vertex;
        while (curr != finish) {
            cnt_edge_in_way++;
            curr = BASearch::min_way_f[curr].first;
        }
    }

    if (percent != nullptr) {
        if (result == std::numeric_limits<CH::weight_t>::max()) *percent = 0;
        else *percent = 100 * cnt_edge_in_way / (double) count_viewed_vertex;
    }

    if (mark_ != nullptr) {
        mark_->assign(BASearch::graph->n, false);
        for (int i = 0; i < BASearch::graph->n; ++i)
            (*mark_)[i] = BASearch::mark[i].first;
    }

    if (cnt_move_ != nullptr)
        *cnt_move_ = count_viewed_vertex;

    if (cnt_edge_in_way_ != nullptr)
        *cnt_edge_in_way_ = cnt_edge_in_way;

    if (Setting::is_debug()) {
        CH::weight_t res = dijkstra_min_two_vertices(start, finish, *graph);
        assert(result == res);
    }

    int time4 = clock();

    std::cout << (time4 - time1) / (double) CLOCKS_PER_SEC << "\n";
    return result;
}
