#include <iostream>
#include <fstream>
#include "includes/structures.h"
#include <set>
#include "includes/writing.h"
#include "includes/reading.h"
#include "TEST/efficiency/a_search_efficiency.h"
#include "TEST/efficiency/dijkstra_efficiency.h"
#include "LANDMARKS/test_efficiency_landmarks.h"


int main() {


    std::string dir = "MyGraphs/graph_data_1k-300k/";

    std::string file_name = "300K_edges.txt";
    std::ifstream in;

    std::string path = dir + file_name;
//
    in.open(path);

    CH::Graph graph = reading_graph(in);
    Setting::set_debug(false);
    ASearch::init(graph);
    BASearch::init(graph);

    std::cout << graph.n << " " << graph.m << "\n";

    int tests = 10;

    std::vector<std::pair<CH::vertex_t, CH::vertex_t> > start_finish_pair(tests);

    for (int i = 0; i < tests; ++i) {
        CH::vertex_t start = Setting::PROJECT_RND() % graph.n;
        CH::vertex_t finish = Setting::PROJECT_RND() % graph.n;

        start_finish_pair[i] = {start, finish};

    }

    int landmarks = 30;
//

    CH::AlgorithmEfficiency E_a_s_slm = a_search_landmarks_average_efficiency_smart_lm(start_finish_pair, graph,
                                                                                       landmarks);
    E_a_s_slm.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";


    CH::AlgorithmEfficiency E_b_a_s_slm = a_search_landmarks_average_efficiency_smart_lm(start_finish_pair, graph,
                                                                                         landmarks, true);
    E_b_a_s_slm.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";

//
    CH::AlgorithmEfficiency E_d = dijkstra_average_efficiency(start_finish_pair, graph);
    E_d.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";


    CH::AlgorithmEfficiency E_b_d = dijkstra_average_efficiency(start_finish_pair, graph, true);
    E_b_d.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";

//
//
    CH::AlgorithmEfficiency E_a_s_rlm = a_search_landmarks_average_efficiency_random_lm(start_finish_pair,
                                                                                       graph, landmarks);
    E_a_s_rlm.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";


    CH::AlgorithmEfficiency E_b_a_s_rlm = a_search_landmarks_average_efficiency_random_lm(start_finish_pair,
                                                                                         graph, landmarks, true);
    E_b_a_s_rlm.print();
    std::cout
            << "------------------------------------------------------------------------------------------------------------------------------------\n";



    return 0;
}
