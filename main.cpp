#include <iostream>
#include "TEST/a_search_test.h"
#include "includes/writing.h"
#include "generate/generate_graphs.h"

int main() {

//    test_simple_dijkstra();
    CH::GridGraph graph = generate_random_grid_graph(5, 6, 10, 4);
    writing_grid_graph(graph, std::cout);

    return 0;
}
