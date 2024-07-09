//
// Created by apple on 03.07.2024.
//

#include "writing.h"
#include <cassert>
#include <map>

void writing_graph(const CH::Graph &graph, std::ostream &out) {
    out << graph.n << " " << graph.m << "\n";
    std::map<std::vector<int>, int> mp;
    for (int v = 0; v < graph.vertices.size(); ++v) {
        for (const CH::Edge &edge : graph.vertices[v].adj) {
            if (mp[{std::min(v, (int)edge.to), std::max(v, (int)edge.to), (int)edge.weight}] % 2 == 0)
                out << v << " " << edge.to << " " << edge.weight << "\n";
            mp[{std::min(v, (int)edge.to), std::max(v, (int)edge.to), (int)edge.weight}]++;
        }
    }
    out << "\n";
}

void writing_grid_graph(const CH::GridGraph &graph, std::ostream &out) {

    auto cols = graph.cols, rows = graph.rows;

    out << rows << " " << cols << "\n";

    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (graph.vertices[get_id(r, c)].degree() == 0) out << "X";
            else out << "O";
        }
        out << "\n";
    }
    out << "\n";
}
