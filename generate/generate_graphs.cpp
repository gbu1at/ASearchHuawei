//
// Created by apple on 02.07.2024.
//

#include "generate_graphs.h"
#include <random>
#include <set>
#include <cassert>
#include <iostream>

CH::Graph generate_random_graph(CH::vertex_t n_vertices, size_t m_edges,
                                CH::weight_t max_weight) {
    assert(m_edges <= n_vertices * (n_vertices - 1) / 2);
    ;

    std::set<std::pair<CH::vertex_t, CH::vertex_t>> edges;

    CH::Graph graph(n_vertices);
    for (size_t _ = 0; _ < m_edges; ++_) {
        do {
            CH::vertex_t a = Setting::PROJECT_RND() % n_vertices;
            CH::vertex_t b = Setting::PROJECT_RND() % n_vertices;
            CH::weight_t w = Setting::PROJECT_RND() % max_weight + 1;
            if (a > b) std::swap(a, b);

            if (a == b) continue;
            if (edges.find({a, b}) != edges.end()) continue;

            edges.insert({a, b});
            graph.add_edge(a, b, w);
            break;
        } while (true);
    }

    std::cout << "random graph created\n";

    return graph;
}

CH::GridGraph generate_random_grid_graph(size_t rows, size_t cols, size_t cnt_block) {
    CH::GridGraph graph(rows, cols);

    std::vector<int> vertices(rows * cols);
    std::iota(vertices.begin(), vertices.end(), 0);

    ;

    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int cur_id = get_id(r, c);
            if (r > 0) {
                int up_id = get_id(r - 1, c);
                if (!graph.has_edge(cur_id, up_id)) {
                    graph.add_edge(cur_id, up_id, 1);
                }
            }
            if (c > 0) {
                int left_id = get_id(r, c - 1);
                if (!graph.has_edge(cur_id, left_id)) {
                    graph.add_edge(cur_id, left_id, 1);
                }
            }
            if (r < rows - 1) {
                int down_id = get_id(r + 1, c);
                if (!graph.has_edge(cur_id, down_id)) {
                    graph.add_edge(cur_id, down_id, 1);
                }
            }
            if (c < cols - 1) {
                int right_id = get_id(r, c + 1);
                if (!graph.has_edge(cur_id, right_id)) {
                    graph.add_edge(cur_id, right_id, 1);
                }
            }
        }
    }

    Setting::shuffle(vertices.begin(), vertices.end());
    vertices.resize(cnt_block);

    for (auto vertex : vertices)
        graph.delete_vertex(vertex);

    return graph;
}

void generate_random_grid_graph(size_t rows, size_t cols, size_t cnt_block, std::ofstream &out) {

}

void
generate_random_graph(CH::vertex_t n_vertices, size_t m_edges, CH::weight_t max_weight, std::ofstream &out) {

}
