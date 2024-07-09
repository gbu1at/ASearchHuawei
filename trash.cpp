//
//std::vector<std::string> files = {"1_5K_edges.txt",
//                                  "1_10K_edges.txt",
//                                  "1_50K_edges.txt",
//                                  "1_100K_edges.txt",
//                                  "2_5K_edges.txt",
//                                  "2_10K_edges.txt",
//                                  "2_50K_edges.txt",
//                                  "2_100K_edges.txt",
//                                  "3_5K_edges.txt",
//                                  "3_10K_edges.txt",
//                                  "3_50K_edges.txt",
//                                  "300K_edges.txt"
//};
//
//
////    files = {"1_5K_edges.txt"};
//
//for (auto file_name : files) {
//std::string path_in = "GRAPHS/graph_data_1k-300k/" + file_name;
//
//std::ifstream in;
//in.open(path_in);
//
//std::string line;
//std::getline(in, line);
//
//int m = stoi(line);
//
//int n = 0;
//
//std::vector<std::vector<int>> edges;
//
//while (m--) {
//std::getline(in, line);
//
//int u, v, w;
//
//
//char delimiter = ' ';
//
//size_t pos1 = std::find(line.begin(), line.end(), delimiter) - line.begin();
//u = stoi(line.substr(0, pos1));
//
//size_t pos2 = std::find(line.begin() + pos1 + 1, line.end(), delimiter) - line.begin();
//v = stoi(line.substr(pos1 + 1, pos2));
//
//
//size_t pos3 = std::find(line.begin() + pos2 + 1, line.end(), delimiter) - line.begin();
//w = stoi(line.substr(pos2 + 1, pos3));
//
//
//edges.push_back({u, v, w});
//n = std::max({n, u, v});
//}
//
//CH::Graph graph(n + 1);
//for (auto &edge : edges)
//graph.add_edge(edge[0], edge[1], edge[2]);
//
//std::string path_out = "MyGraphs/graph_data_1k-300k/" + file_name;
//std::ofstream  out;
//out.open(path_out);
//
//writing_graph(graph, out);
//
//in.close();
//out.close();
//}