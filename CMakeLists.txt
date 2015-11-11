cmake_minimum_required(VERSION 2.8)
project(sanajahti1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -pedantic -std=c++11")
add_executable(sanajahti1 src/main.cpp)

add_library(Solvers
        src/solver.cpp
        src/solver.hpp
        src/trie.cpp
        src/trie.hpp
)

target_link_libraries(sanajahti1 Solvers)