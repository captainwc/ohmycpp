cmake_minimum_required(VERSION 3.16)
project(moderncpp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(example)
add_subdirectory(test)
add_subdirectory(leetcode)