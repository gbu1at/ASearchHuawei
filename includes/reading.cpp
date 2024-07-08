//
// Created by apple on 02.07.2024.
//

#include "reading.h"

CH::Graph reading_graph(std::istream &in) {
    int n, m;
    in >> n >> m;
    CH::Graph graph(n);
    for (int _ = 0; _ < m; ++_) {
        int v, u, w; in >> v >> u >> w;
        graph.add_edge(v, u, w);
    }
    std::cout << "reading is worked!\n";

    return graph;
}

CH::GridGraph reading_grid_graph(std::istream& in) {
    int rows, cols;
    in >> rows >> cols;

    CH::GridGraph graph(rows, cols);
    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char x; in >> x;
            if (x == 'X') graph.delete_vertex(get_id(r, c));
        }
    }

    std::cout << "reading is worked!\n";

    return graph;
}
