//
// Created by apple on 04.07.2024.
//

#include "a_search_efficiency.h"
#include "../../LANDMARKS/landmarks.h"


CH::AlgorithmEfficiency a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                            std::function<CH::weight_t(CH::vertex_t)> p
) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    E.result = a_search(start, finish, graph, p, &E.percent, nullptr, &E.cnt_move, &E.cnt_edge_in_way);

    E.name_algorithm = "a_search";

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}


CH::AlgorithmEfficiency B_a_search_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph,
                                              std::function<CH::weight_t(CH::vertex_t)> p_s,
                                              std::function<CH::weight_t(CH::vertex_t)> p_f) {
    CH::AlgorithmEfficiency E;

    clock_t time_start = clock();

    E.result = B_a_search(start, finish, graph, p_s, p_f, &E.percent, nullptr, &E.cnt_move, &E.cnt_edge_in_way);
    E.name_algorithm = "B_a_search";

    clock_t time_finish = clock();

    E.time = (time_finish - time_start) / (double) CLOCKS_PER_SEC;

    return E;
}

CH::AlgorithmEfficiency
a_search_manhattan_distance_average_efficiency(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::GridGraph &graph,
                                               bool is_B_search) {
    double average_percent = 0;
    double average_time = 0;
    CH::weight_t result = 0;
    int cnt_move = 0;
    int cnt_edge_in_way = 0;
    int N = 0;

    int tests = pair_start_finish.size();

    for (int _ = 0; _ < tests; ++_) {
        auto[start, finish] = pair_start_finish[_];

        CH::AlgorithmEfficiency E = a_search_manhattan_distance_efficiency(start, finish, graph, is_B_search);
        if (E.result != std::numeric_limits<CH::weight_t>::max()) {
            average_percent += E.percent;
            average_time += E.time;
            result += E.result;
            cnt_move += E.cnt_move;
            cnt_edge_in_way += E.cnt_edge_in_way;
            N++;
        }
    }
    CH::AlgorithmEfficiency E;
    E.percent = average_percent / N;
    E.time = average_time / N;
    E.result = result / N;
    E.cnt_move = cnt_move / N;
    E.cnt_edge_in_way = cnt_edge_in_way / N;
    if (!is_B_search) {
        E.comment = "a search + manhattan distance";
        E.name_algorithm = "a search";
    } else {
        E.comment = "B + a search + manhattan distance";
        E.name_algorithm = "B + a search";
    }
    return E;
}


CH::AlgorithmEfficiency
a_search_manhattan_distance_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::GridGraph &graph,
                                       bool is_B_search) {

    size_t rows = graph.rows, cols = graph.cols;
    size_t n = graph.n;

    auto get_cell = [cols](CH::vertex_t id) {
        return std::make_pair(id / cols, id % cols);
    };

    auto get_id = [cols](int row, int col) {
        return row * cols + col;
    };

    std::vector<CH::weight_t> p_s(n), p_f(n);

    auto [start_row, start_col] = get_cell(start);
    auto [finish_row, finish_col] = get_cell(finish);

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col) {
            p_s[get_id(row, col)] = abs((int) finish_row - row) + abs((int) finish_col - col);
            p_f[get_id(row, col)] = abs((int) start_row - row) + abs((int) start_col - col);
        }

    CH::AlgorithmEfficiency E;

    std::function<CH::weight_t(CH::vertex_t)> p_s_func = [&p_s](CH::vertex_t v) {
        return p_s[v];
    };

    std::function<CH::weight_t(CH::vertex_t)> p_f_func = [&p_f](CH::vertex_t v) {
        return p_f[v];
    };

    if (!is_B_search)
        E = a_search_efficiency(start, finish, graph, p_s_func);
    else
        E = B_a_search_efficiency(start, finish, graph, p_s_func, p_f_func);

    return E;
}


CH::AlgorithmEfficiency
a_search_landmarks_efficiency(CH::vertex_t start, CH::vertex_t finish, const CH::Graph &graph, CH::LandMarks lm,
                              bool is_B_search) {

    CH::LandMarks lm_s = std::move(lm);
    lm_s.set_finish(finish);

    std::function<CH::weight_t(CH::vertex_t)> get_dist_s = [&lm_s](CH::vertex_t v) {
        return lm_s.get_dist(v);
    };

    CH::LandMarks lm_f = lm_s;
    lm_f.set_finish(start);

    std::function<CH::weight_t(CH::vertex_t)> get_dist_f = [&lm_f](CH::vertex_t v) {
        return lm_f.get_dist(v);
    };


    CH::AlgorithmEfficiency E;
    if (!is_B_search) {
        E = a_search_efficiency(start, finish, graph, get_dist_s);
        E.comment = "a search + landmarks cnt: " + std::to_string(lm.cnt_landmarks);
    } else {
        E = B_a_search_efficiency(start, finish, graph, get_dist_s, get_dist_f);
        E.comment = "B + a search + landmarks cnt: " + std::to_string(lm.cnt_landmarks);
    }

    return E;
}


CH::AlgorithmEfficiency
a_search_landmarks_average_efficiency(const std::vector<std::pair<CH::vertex_t, CH::vertex_t>> & pair_start_finish, const CH::Graph &graph, const CH::LandMarks &lm,
                                      bool is_B_search) {

    double average_percent = 0;
    double average_time = 0;
    CH::weight_t result = 0;
    int cnt_move = 0;
    int cnt_edge_in_way = 0;
    int N = 0;

    int tests = pair_start_finish.size();

    for (int _ = 0; _ < tests; ++_) {
        auto[start, finish] = pair_start_finish[_];

        CH::AlgorithmEfficiency E = a_search_landmarks_efficiency(start, finish, graph, lm, is_B_search);
        if (E.result != std::numeric_limits<CH::weight_t>::max()) {
            average_percent += E.percent;
            average_time += E.time;
            result += E.result;
            cnt_move += E.cnt_move;
            cnt_edge_in_way += E.cnt_edge_in_way;
            N++;
        }
    }
    CH::AlgorithmEfficiency E;
    E.percent = average_percent / N;
    E.time = average_time / N;
    E.result = result / N;
    E.cnt_move = cnt_move / N;
    E.cnt_edge_in_way = cnt_edge_in_way / N;
    if (!is_B_search) {
        E.comment = "a search + landmarks cnt: " + std::to_string(lm.cnt_landmarks);
        E.name_algorithm = "a search";
    } else {
        E.comment = "B + a search + landmarks cnt: " + std::to_string(lm.cnt_landmarks);
        E.name_algorithm = "B + a search";
    }


    return E;
}