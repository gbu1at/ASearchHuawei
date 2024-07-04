//
// Created by apple on 02.07.2024.
//

#ifndef ASEARCH_STRUCTURES_H
#define ASEARCH_STRUCTURES_H

#include "types.h"
#include <cstdint>
#include <cstdio>
#include <vector>
#include <string>

namespace CH {
    struct Edge;
    struct Vertex;
    struct Graph;

    struct Edge {
        vertex_t to;
        weight_t weight;
        size_t id;

        Edge(vertex_t t, vertex_t f, weight_t w, size_t u);
    };

    struct Vertex {
        std::vector<Edge> adj;

        Vertex();

        size_t degree() const {
            return this->adj.size();
        }
    };

    struct Graph {
        std::vector<Vertex> vertices;
        // n - cnt vertex
        // m - cnt edges

        size_t n;
        size_t m;

        Graph();

        explicit Graph(size_t n_vertices);

        void add_edge(vertex_t a, vertex_t b, weight_t w);

        // O(deg(a));
        bool has_edge(vertex_t a, vertex_t b);

        void erase_edge(vertex_t a, vertex_t b);
    };

    struct GridGraph : Graph {
        GridGraph(size_t rows, size_t cols);
        GridGraph();
        size_t rows, cols;
        bool is_deleted_vertex(int row, int col);
        int get_id(int row, int col) const;
    };

    struct AlgorithmEfficiency {
        double percent;
        double time;
        weight_t result;
        std::string name_algorithm;
        void print() const;
    };
};

#endif //ASEARCH_STRUCTURES_H
