//
// Created by apple on 02.07.2024.
//

#ifndef ASEARCH_GENERATE_GRAPHS_H
#define ASEARCH_GENERATE_GRAPHS_H

#include "../includes/structures.h"
#include <fstream>

// Генерирует рандомный граф на n вершинах, m ребрах и с максимальным диапазоном ребер до max_weight
CH::Graph
generate_random_graph(CH::vertex_t n_vertices, size_t m_edges, CH::weight_t max_weight = RandomUtil::PROJECT_RND());

void generate_random_graph(CH::vertex_t n_vertices, size_t m_edges, CH::weight_t max_weight, std::ofstream &out);


// Генерирует рандомную граф-доску, со стороной rows и с шириной cols
// Где cnt_block - количество заблокированных вершин
CH::GridGraph generate_random_grid_graph(size_t rows, size_t cols, size_t cnt_block);

void generate_random_grid_graph(size_t rows, size_t cols, size_t cnt_block, std::ofstream &out);


#endif //ASEARCH_GENERATE_GRAPHS_H
