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
        TEST/a_search_test.h
)
