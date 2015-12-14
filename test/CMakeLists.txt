cmake_minimum_required(VERSION 2.8.12)
project(sanajahti1)
set(CMAKE_PREFIX_PATH "/Users/jma/Qt/5.5/clang_64/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -pedantic -std=c++11")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
ADD_SUBDIRECTORY (gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# Tell CMake to create the helloworld executable
add_executable(sanajahti_test test_sanajahti.cpp)

add_library(deps
        ../src/to64bitchars.cpp
        ../src/to64bitchars.hpp)

# Use the Widgets module from Qt 5.
target_link_libraries(deps Qt5::Widgets)
target_link_libraries(sanajahti_test gtest gtest_main)
target_link_libraries(sanajahti_test deps)