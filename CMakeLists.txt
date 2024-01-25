cmake_minimum_required(VERSION 3.16)
project(leetcode)

# 什么年代了，谁还用传统 C 嘎嘎
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 这个变量是默认的吗？AI说是，可是没有补全。可若不是，设置后编译选项也确实传进去了。应当是默认的吧，懒得深究了
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# message("System: ${CMAKE_SYSTEM_NAME}")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    message(WARNING "主要还是在 Linux 环境下开发，如果要移植到 windows 下，找库这一块好好改改")
    # set(GTEST_ROOT D:/env/mingw64/lib/gcc/x86_64-w64-mingw32/13.2.0)
    find_library(GTEST_LIB NAMES gtest PATHS ${GTEST_ROOT} REQUIRED)
    find_library(GTEST_MAIN_LIB NAMES gtest_main PATHS ${GTEST_ROOT} REQUIRED)
    message(STATUS "Lib [gtest] found: ${GTEST_LIB}")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_library(GTEST_LIB NAMES gtest REQUIRED)
    find_library(GTEST_MAIN_LIB NAMES gtest_main REQUIRED)
    if(GTEST_LIB)
        message(STATUS "Lib [gtest] found: ${GTEST_LIB}")
    endif()
    if(GTEST_MAIN_LIB)
        message(STATUS "Lib [gtest_main] found: ${GTEST_MAIN_LIB}")
    endif()
else()
    message(WARNING "I haven't used MacOS or other magic platform. You may fix it yourself")
endif()

# 把这个关了src总是找不到头文件也很烦。加，都可以加
option(BUILD_SRC "Build source code" ON)

if(BUILD_SRC)
    message(STATUS "[ON] Build Src Dir")
    add_subdirectory(src)
else()
    message(STATUS "[OFF] Build Src Dir")
endif()

# 这里也很有意思，如果先add，那么GTEST_LIB就会在子文件的cmakelist解析之后才找到，那可能会出问题吧。可以通过message看先后顺序
add_subdirectory(test)
add_subdirectory(examples)
