set(SOURCES listTest.cpp treeTest.cpp treeTest2.cpp)

include_directories(../../include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

foreach(file ${SOURCES})
    string(REGEX REPLACE ".cpp$" "" target_name ${file})
    add_executable(${target_name} ${file})
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/include)
    # TODO 这里有没有好办法，不用每一个都链接这个
    target_sources(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/include/list/ListNode.cpp)
    target_link_libraries(${target_name} PUBLIC ${GTEST_LIB} ${GTEST_MAIN_LIB})
    install(TARGETS ${target_name} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()
