set(SOURCES listTest.cpp treeTest.cpp treeTest2.cpp)

include_directories(../../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

foreach(file ${SOURCES})
    string(REGEX REPLACE ".cpp$" "" target_name ${file})
    add_executable(${target_name} ${file})
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/../include)
    target_link_libraries(${target_name} PUBLIC ${GTEST_LIB} ${GTEST_MAIN_LIB})
    install(TARGETS ${target_name} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
