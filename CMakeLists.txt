cmake_minimum_required(VERSION 3.16)
project(leetcode)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# 把这个关了src总是找不到头文件也很烦。加，都可以加
option(BUILD_SRC "Build source code" ON)

if (BUILD_SRC)
    add_subdirectory(src)
endif ()

message("System: "${CMAKE_SYSTEM_NAME})
if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    # set(GTEST_ROOT D:/env/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0)
    find_library(GTEST_LIB NAMES gtest PATHS ${GTEST_ROOT} REQUIRED)
    find_library(GTEST_MAIN_LIB NAMES gtest_main PATHS ${GTEST_ROOT} REQUIRED)
    message("Lib [gtest] found: "${GTEST_LIB})
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_library(GTEST_LIB NAMES gtest REQUIRED)
    find_library(GTEST_MAIN_LIB NAMES gtest_main REQUIRED)
    message("Lib [gtest] found: "${GTEST_LIB})
    message("Lib [gtest_main] found: "${GTEST_LIB})
else ()
    message("I haven't used MacOS or other magic platform. You may fix it yourself")
endif ()

add_subdirectory(test)
add_subdirectory(examples)