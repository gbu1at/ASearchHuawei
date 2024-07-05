//
// Created by apple on 02.07.2024.
//

#include "structures.h"
#include "types.h"
#include <iostream>

//void CH::set_seed(int new_seed) {
//    CH::SEED = new_seed;
//    RandomUtil::PROJECT_RND.seed(new_seed);
//}

CH::Edge::Edge(CH::vertex_t t, CH::vertex_t f, CH::weight_t w, size_t i) {
    this->to = t;
    this->weight = w;
    this->id = i;
}

CH::Vertex::Vertex() = default;

CH::Graph::Graph(size_t n_vertices) {
    this->n = n_vertices;
    this->m = 0;
    this->vertices = std::vector<Vertex>(n_vertices);
}

CH::Graph::Graph() : Graph(0) {}

void CH::Graph::add_edge(CH::vertex_t a, CH::vertex_t b, CH::weight_t w) {
    this->vertices[a].adj.emplace_back(b, a, w, m);
    this->vertices[b].adj.emplace_back(a, b, w, m);
    m++;
}

bool CH::Graph::has_edge(CH::vertex_t a, CH::vertex_t b) {
    for (const Edge& edge : this->vertices[a].adj) if (edge.to == b) return true;
    return false;
}

void CH::Graph::erase_edge(CH::vertex_t a, CH::vertex_t b) {

}

void CH::Graph::print() {
    std::cout << n << " " << m << "\n";
    for (int v = 0; v < n; ++v) {
        std::cout << v << ": ";
        for (auto edge : vertices[v].adj) {
            std::cout << edge.to << " " << edge.weight << " ;\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void CH::Graph::delete_vertex(CH::vertex_t vertex) {
    for (auto&  edge : vertices[vertex].adj) {
        auto u = edge.to;
        vertices[u].adj.erase(std::remove_if(vertices[u].adj.begin(), vertices[u].adj.end(), [vertex](const CH::Edge& edge) {
            return edge.to == vertex;
        }), vertices[u].adj.end());
    }
    vertices[vertex].adj.clear();
}

CH::GridGraph::GridGraph(size_t rows, size_t cols) : Graph(rows * cols) {
    this->rows = rows;
    this->cols = cols;
    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int cur_id = get_id(r, c);
            if (r > 0) {
                int up_id = get_id(r - 1, c);
                if (!has_edge(cur_id, up_id)) {
                    add_edge(cur_id, up_id, 1);
                }
            }
            if (c > 0) {
                int left_id = get_id(r, c - 1);
                if (!has_edge(cur_id, left_id)) {
                    add_edge(cur_id, left_id, 1);
                }
            }
            if (r < rows - 1) {
                int down_id = get_id(r + 1, c);
                if (!has_edge(cur_id, down_id)) {
                    add_edge(cur_id, down_id, 1);
                }
            }
            if (c < cols - 1) {
                int right_id = get_id(r, c + 1);
                if (!has_edge(cur_id, right_id)) {
                    add_edge(cur_id, right_id, 1);
                }
            }
        }
    }
}

CH::GridGraph::GridGraph() : Graph() {
    this->rows = 0;
    this->cols = 0;
}

bool CH::GridGraph::is_deleted_vertex(int row, int col) {
    int v = this->get_id(row, col);
    return vertices[v].degree() == 0;
}

int CH::GridGraph::get_id(int row, int col) const {
    return row * this->cols + col;
}
void CH::AlgorithmEfficiency::print() const
{
    std::cout << "\n"
              << "algorithm: " << name_algorithm << "\n"
              << "time: " << time << "\n"
              << "percent: " << percent << "\n"
              << "result: " << result << "\n"
              << "cnt move: " << cnt_move << "\n"
              << "cnt edge in way: " << cnt_edge_in_way << "\n"
              << "comment: '''" << comment << "''''" << "\n"
              << "\n";
}
