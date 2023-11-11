cmake_minimum_required(VERSION 3.16)
project(leetcode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

option(BUILD_SRC "Build source code" OFF)

if (BUILD_SRC)
    add_subdirectory(src)
endif ()

set(GTEST_ROOT C:/ENV/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0)
find_library(GTEST_LIB NAMES gtest PATHS ${GTEST_ROOT} REQUIRED)
find_library(GTEST_MAIN_LIB NAMES gtest_main PATHS ${GTEST_ROOT} REQUIRED)

add_subdirectory(test)
add_subdirectory(examples)