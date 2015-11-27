cmake_minimum_required(VERSION 3.3)
project(sanajahti1)
set(CMAKE_PREFIX_PATH "/Users/jma/Qt/5.5/clang_64/lib/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -pedantic -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(sanajahti1 WIN32 src/main.cpp)

add_library(deps
        src/solver.cpp
        src/solver.hpp
        src/trie.cpp
        src/trie.hpp
        src/UI.cpp
        src/UI.hpp
        src/adb_screenshot.cpp
        src/adb_screenshot.hpp
        src/window.cpp
        src/window.hpp
        src/ocr.hpp
        src/ocr.cpp
        src/console.cpp
        src/console.hpp
        )

# Use the Widgets module from Qt 5.
target_link_libraries(deps Qt5::Widgets)
target_link_libraries(sanajahti1 deps)