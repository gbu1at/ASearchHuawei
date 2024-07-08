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

//    std::ofstream out;
//    out.open("1e3-1e3-2e5 grid.txt");
//
//    CH::GridGraph g = generate_random_grid_graph(1e3, 1e3, 2e5);
//
//    writing_grid_graph(g, out);
//    out.close();



    std::ifstream in("1e3-1e3-2e5 grid.txt");

    CH::GridGraph graph = reading_grid_graph(in);
//
//    Setting::initializeSeed(9454359);
////    Setting::set_debug(true);
//
//
    int tests = 200;
//
    std::vector<std::pair<CH::vertex_t , CH::vertex_t>> pair_start_finish(tests);
////
    for (int i = 0; i < tests; ++i) {
        CH::vertex_t start = Setting::PROJECT_RND() % graph.n;
        CH::vertex_t finish = Setting::PROJECT_RND() % graph.n;

        pair_start_finish[i] = {start, finish};
    }
//
//    std::cout << "start\n";
    int cnt_landmark = 16;
//
    CH::AlgorithmEfficiency E_a_r_lm = a_search_landmarks_average_efficiency_random_lm(pair_start_finish, graph, cnt_landmark);
    E_a_r_lm.print();
//    std::cout << "-------------------------------------------------\n";
//
    CH::AlgorithmEfficiency E_a_s_lm = a_search_landmarks_average_efficiency_smart_lm(pair_start_finish, graph, cnt_landmark);
    E_a_s_lm.print();

    std::cout << "-------------------------------------------------\n";
//
    CH::AlgorithmEfficiency E_b_a_r_lm = a_search_landmarks_average_efficiency_random_lm(pair_start_finish, graph, cnt_landmark, true);
    E_b_a_r_lm.print();

    std::cout << "-------------------------------------------------\n";
//
    CH::AlgorithmEfficiency E_b_a_s_lm = a_search_landmarks_average_efficiency_smart_lm(pair_start_finish, graph, cnt_landmark, true);
    E_b_a_s_lm.print();

    std::cout << "-------------------------------------------------\n";
//
    CH::AlgorithmEfficiency E_d = dijkstra_average_efficiency(pair_start_finish, graph);
    E_d.print();
    std::cout << "-------------------------------------------------\n";
//
//
    CH::AlgorithmEfficiency E_b_d = dijkstra_average_efficiency(pair_start_finish, graph, true);
    E_b_d.print();
    std::cout << "-------------------------------------------------\n";


    CH::AlgorithmEfficiency E_a_man_dist = dijkstra_average_efficiency(pair_start_finish, graph);
    E_a_man_dist.print();
    std::cout << "-------------------------------------------------\n";


    CH::AlgorithmEfficiency E_b_a_man_dist = dijkstra_average_efficiency(pair_start_finish, graph, true);
    E_b_a_man_dist.print();

    std::cout << "-------------------------------------------------\n";

    return 0;
}
