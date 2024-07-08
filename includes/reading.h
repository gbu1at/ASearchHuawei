//
// Created by apple on 02.07.2024.
//

#ifndef ASEARCH_READING_H
#define ASEARCH_READING_H

#include "structures.h"
#include <fstream>
#include <iostream>

CH::Graph reading_graph(std::istream& in = std::cin);
void reading_grid_graph(std::istream& in = std::cin);

#endif //ASEARCH_READING_H
