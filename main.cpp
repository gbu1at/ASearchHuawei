#include <iostream>
#include "TEST/efficiency/test_efficiency.h"

int main() {

    std::cout << "OK\n";

    for (int test = 0; test < 1; ++test) {
        std::cout << test << "\n";
        test_manhattan_graph_efficiency(test);
    }
//    test_manhattan_graph_efficiency();


    return 0;
}
