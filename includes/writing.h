//
// Created by apple on 03.07.2024.
//

#ifndef ASEARCH_WRITING_H
#define ASEARCH_WRITING_H

#include <fstream>
#include <iostream>
#include "structures.h"

void writing_graph(const CH::Graph& graph, std::ostream& out = std::cout);
void writing_grid_graph(const CH::GridGraph& graph, std::ostream& out = std::cout);


#endif //ASEARCH_WRITING_H
