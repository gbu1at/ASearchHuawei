//
// Created by apple on 02.07.2024.
//

#include "structures.h"
#include "types.h"
#include <fstream>
#include <iostream>

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

CH::GridGraph::GridGraph(size_t rows, size_t cols) : Graph(rows * cols) {
    this->rows = rows;
    this->cols = cols;
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
              << "\n";
}
