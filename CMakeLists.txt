cmake_minimum_required(VERSION 2.8.12)
project(sanajahti1)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -pedantic -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
add_executable(sanajahti1 src/main.cpp)

add_library(deps
        src/solver.cpp
        src/solver.hpp
        src/trie.cpp
        src/trie.hpp
        src/ui.cpp
        src/ui.hpp
        src/adb_screenshot.cpp
        src/adb_screenshot.hpp
        src/window.cpp
        src/window.hpp
        src/ocr.hpp
        src/ocr.cpp
        src/console.cpp
        src/console.hpp
        src/to64bitchars.cpp
        src/to64bitchars.hpp
        src/solver_thread.cpp
        src/solver_thread.hpp)

target_link_libraries(deps Qt5::Widgets)
target_link_libraries(sanajahti1 deps)