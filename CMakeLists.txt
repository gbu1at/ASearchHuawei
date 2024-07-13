cmake_minimum_required(VERSION 3.28)
project(ASearch)

set(CMAKE_CXX_STANDARD 17)

add_executable(ASearch main.cpp
        includes/structures.h
        includes/structures.cpp
        includes/types.h
        includes/reading.h
        includes/reading.cpp
        generate/generate_graphs.h
        generate/generate_graphs.cpp
        a_search.cpp
        ALGO/dijkstra.h
        ALGO/dijkstra.cpp
        ALGO/asearch.h
        ALGO/asearch.cpp
        includes/writing.h
        includes/writing.cpp
        TEST/tests/a_search_test.cpp
        efficiency/a_search_efficiency.h
        efficiency/a_search_efficiency.cpp
        efficiency/test_efficiency.h
        efficiency/test_efficiency.cpp
        LANDMARKS/landmarks.h
        LANDMARKS/landmarks.cpp
        setting.h
        setting.cpp
        efficiency/dijkstra_efficiency.h
        efficiency/dijkstra_efficiency.cpp
        LANDMARKS/efficiency_landmarks.h
        LANDMARKS/efficiency_landmarks.cpp
        TEST/tests/testin_all_algorithm.cpp
)
