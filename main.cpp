#include <iostream>
#include <fstream>
#include "includes/structures.h"
#include <set>
#include "includes/writing.h"
#include "includes/reading.h"
#include "efficiency/a_search_efficiency.h"
#include "efficiency/dijkstra_efficiency.h"
#include "LANDMARKS/efficiency_landmarks.h"


int main() {

    int time_start = clock();

    std::string dir = "MyGraphs/graph_data_1k-300k/";
    std::string file_name = "300K_edges.txt";

    CH::Graph graph = reading_graph(dir + file_name);
    Setting::set_debug(false);
//    Setting::initializeSeed(283635);
    Setting::initializeSeed(4356);
    ASearch::init(graph);
    BASearch::init(graph);
    Dijkstra::init(graph);
    BDijkstra::init(graph);

    std::cout << graph.n << " " << graph.m << "\n";

    int tests = 100;

    std::vector<std::pair<CH::vertex_t, CH::vertex_t> > start_finish_pair(tests);

    for (int i = 0; i < tests; ++i) {
        CH::vertex_t start = Setting::PROJECT_RND() % graph.n;
        CH::vertex_t finish = Setting::PROJECT_RND() % graph.n;
        start_finish_pair[i] = {start, finish};
    }

//    start_finish_pair = {{2, 5}};

    int landmarks = 100;
    int active_landmarks = 2;


    CH::AlgorithmEfficiency E_b_d = dijkstra_average_efficiency(start_finish_pair, graph, true);
    E_b_d.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";

////
//    CH::AlgorithmEfficiency E_d = dijkstra_average_efficiency(start_finish_pair, graph);
//    E_d.print();
//    std::cout
//            << "------------------------------------------------------------------------------------------------------------------------------------\n";
////


//    CH::AlgorithmEfficiency E_a_s_rlm = a_search_landmarks_average_efficiency_random_lm(start_finish_pair,
//                                                                                       graph, landmarks, active_landmarks);
//    E_a_s_rlm.print();
//    std::cout
//            << "------------------------------------------------------------------------------------------------------------------------------------\n";

    CH::AlgorithmEfficiency E_b_a_s_slm = a_search_landmarks_average_efficiency_smart_lm(start_finish_pair, graph,
                                                                                         landmarks, active_landmarks, true);
    E_b_a_s_slm.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";

//    CH::AlgorithmEfficiency E_a_s_slm = a_search_landmarks_average_efficiency_smart_lm(start_finish_pair, graph,
//                                                                                       landmarks, active_landmarks);
//    E_a_s_slm.print();
//    std::cout
//            << "------------------------------------------------------------------------------------------------------------------------------------\n";

////
////

//
//    CH::AlgorithmEfficiency E_b_a_s_rlm = a_search_landmarks_average_efficiency_random_lm(start_finish_pair,
//                                                                                         graph, landmarks, true);
//    E_b_a_s_rlm.print();
//    std::cout
//            << "------------------------------------------------------------------------------------------------------------------------------------\n";

    int time_finish = clock();

    std::cout << (time_finish - time_start) / (double) CLOCKS_PER_SEC << "\n";

    return 0;
}
