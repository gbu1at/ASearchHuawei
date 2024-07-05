#include <iostream>
#include "TEST/efficiency/dijkstra_efficiency.h"
#include "generate/generate_graphs.h"
#include "TEST/tests/a_search_test.h"
#include "setting.h"
#include "LANDMARKS/test_efficiency_landmarks.h"

int main() {
    test_simple_dijkstra();


//    for (int i = 0; i < 5; ++i) {
//        Setting::initializeSeed(i);
//        test_random_graph_efficiency();
//        std::cout << "OK " << i << "\n";
//    }

    Setting::initializeSeed(time(nullptr));
    Setting::set_debug(false);

    int cnt_landmark = 16;
    int tests = 1;

    CH::Graph graph = generate_random_graph(10000, 50000, 20);

    std::cout << "graph generate!\n";

    CH::AlgorithmEfficiency E1 = a_search_landmarks_average_efficiency_smart_lm(tests, graph, cnt_landmark);
    E1.print();

//    CH::AlgorithmEfficiency E2 = a_search_landmarks_average_efficiency_smart_lm(tests, graph, cnt_landmark, true);
    CH::AlgorithmEfficiency E3 = dijkstra_average_efficiency(tests, graph);
//    CH::AlgorithmEfficiency E4 = dijkstra_average_efficiency(tests, graph, true);

//    E2.print();
    E3.print();
//    E4.print();

//    Setting::initializeSeed(6);
//    test_random_graph_efficiency();
////    test_random_graph_efficiency();

    return 0;
}
