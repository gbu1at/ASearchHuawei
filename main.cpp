#include <iostream>
#include "TEST/efficiency/test_efficiency.h"
#include "generate/generate_graphs.h"
#include "TEST/tests/a_search_test.h"
#include "random_until.h"

int main() {
    test_simple_dijkstra();


//    for (int i = 0; i < 5; ++i) {
//        RandomUtil::initializeSeed(i);
//        test_random_graph_efficiency();
//        std::cout << "OK " << i << "\n";
//    }

    RandomUtil::initializeSeed(time(nullptr));
    test_random_graph_efficiency(16);

//    RandomUtil::initializeSeed(6);
//    test_random_graph_efficiency();
////    test_random_graph_efficiency();

    return 0;
}
