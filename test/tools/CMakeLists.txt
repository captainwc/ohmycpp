set(SOURCES
    loggerTest.cpp
    progressBar.cpp
    stringTest.cpp
)

include_directories(../../include)

# 同级都设置过这个 -pthread，但是平级不重复。同一树枝上才累加
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

foreach(file ${SOURCES})
    string(REGEX REPLACE ".cpp$" "" target_name ${file})
    add_executable(${target_name} ${file})
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/../include)
    target_link_libraries(${target_name} PUBLIC ${GTEST_LIB} ${GTEST_MAIN_LIB})
endforeach()