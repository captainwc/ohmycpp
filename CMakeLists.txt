cmake_minimum_required(VERSION 3.16)
project(leetcode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

option(BUILD_SRC "Build source code" OFF)

if(BUILD_SRC)
    add_subdirectory(src)
endif()

add_subdirectory(test)
add_subdirectory(examples)