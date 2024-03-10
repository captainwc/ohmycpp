# basic config

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(LOG_DIR ${CMAKE_SOURCE_DIR}/log)
set(CPP_CHECK_DIR ${LOG_DIR}/cppcheck)

# Project Module
option(BUILD_SRC "Add leetcode SRC target" ON)
option(BUILD_TEST "Build Example and Test" ON)

include(${CMAKE_SOURCE_DIR}/cmake/library.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/tools.cmake)

if(BUILD_SRC)
    add_subdirectory(leetcode)
endif()
if(BUILD_TEST)
    add_subdirectory(example)
    add_subdirectory(test)
endif()

# CXX
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

option(WERROR "if -Werror" ON)
if(WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

find_program(CPP_CHECK "cppcheck")
