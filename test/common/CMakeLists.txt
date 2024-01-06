set(SOURCES ansiTest.cpp smartPtrTest.cpp)

include_directories(../../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

foreach(file ${SOURCES})
    string(REGEX REPLACE ".cpp$" "" target_name ${file})
    add_executable(${target_name} ${file})
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/../include)
    if(GTEST_LIB)
        target_link_libraries(${target_name} PUBLIC ${GTEST_LIB} ${GTEST_MAIN_LIB})
    endif()
endforeach()
