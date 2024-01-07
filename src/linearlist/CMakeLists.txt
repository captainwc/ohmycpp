set(SOURCES 19rmNthFromEnd.cpp 24swapPairs.cpp 61rotateRightList.cpp)

include_directories(../../include)

foreach(file ${SOURCES})
    string(REGEX REPLACE ".cpp$" "" target_name ${file})
    add_executable(${target_name} ${file})
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/include)
    target_sources(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/include/list/ListNode.cpp)
endforeach()
