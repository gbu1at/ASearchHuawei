#include <iostream>
#include "TEST/efficiency/dijkstra_efficiency.h"
#include "generate/generate_graphs.h"
#include "TEST/tests/a_search_test.h"
#include "setting.h"
#include "LANDMARKS/test_efficiency_landmarks.h"
#include "includes/reading.h"
#include "includes/writing.h"


#include <iostream>
#include <fstream>



int main() {
//    test_simple_dijkstra();
//
//
//    int cnt_landmark = 10;

//    std::ofstream out;
//    out.open("2e4-4e6-1e4 rnd.txt");
//
////    out << 1 << "\n";
//    CH::Graph graph = generate_random_graph(20000, 4000000, 10000);
//
//    writing_graph(graph, out);
//    out.close();


//    CH::Graph graph = generate_random_graph(200000, 1000000, 10000);
//    std::cout << "generate graph\n";



    std::ifstream in("2e5-2e6-1e5 rnd.txt");

    CH::Graph graph = reading_graph(in);

    Setting::initializeSeed(9454359);


    int tests = 200;

    std::vector<std::pair<CH::vertex_t , CH::vertex_t>> pair_start_finish(tests);

    for (int i = 0; i < tests; ++i) {
        CH::vertex_t start = Setting::PROJECT_RND() % graph.n;
        CH::vertex_t finish = Setting::PROJECT_RND() % graph.n;

        pair_start_finish[i] = {start, finish};
    }
//
//    std::cout << "start\n";
    int cnt_landmark = 16;
//
//    CH::AlgorithmEfficiency E_a_r_lm = a_search_landmarks_average_efficiency_random_lm(pair_start_finish, graph, cnt_landmark);
//    E_a_r_lm.print();
//
//
//    std::cout << "-------------------------------------------------\n";
//
    CH::AlgorithmEfficiency E_a_s_lm = a_search_landmarks_average_efficiency_smart_lm(pair_start_finish, graph, cnt_landmark);
    E_a_s_lm.print();
//
//    std::cout << "-------------------------------------------------\n";
//
//    CH::AlgorithmEfficiency E_b_a_r_lm = a_search_landmarks_average_efficiency_random_lm(pair_start_finish, graph, cnt_landmark, true);
//    E_b_a_r_lm.print();
//
//    std::cout << "-------------------------------------------------\n";
//
//    CH::AlgorithmEfficiency E_b_a_s_lm = a_search_landmarks_average_efficiency_smart_lm(pair_start_finish, graph, cnt_landmark, true);
//    E_b_a_s_lm.print();
//
//    std::cout << "-------------------------------------------------\n";
//
//    CH::AlgorithmEfficiency E_d = dijkstra_average_efficiency(pair_start_finish, graph);
//    E_d.print();
//    std::cout << "-------------------------------------------------\n";
//
//
//    CH::AlgorithmEfficiency E_b_d = dijkstra_average_efficiency(pair_start_finish, graph, true);
//    E_b_d.print();
//    std::cout << "-------------------------------------------------\n";


    return 0;
}
