set(TARGETS "[Tests]: ")

set(COMMON_TEST graphicTest.cpp lctest.cpp utilsTest.cpp)

foreach (test_file ${COMMON_TEST})
    STRING(REGEX REPLACE ".cpp" "" target ${test_file})
    add_executable(${target} ${test_file})
    target_include_directories(${target} PUBLIC ${INCLUDE_DIR})
    set(TARGETS "${TARGETS} ${target}")
endforeach ()

if (LIB_REDIS)
    add_executable(redisTest redisTest.cpp)
    target_include_directories(${redidTest} PUBLIC ${INCLUDE_DIR})
    target_link_libraries(${redisTest} PUBLIC ${LIB_REDIS})
    set(TARGETS "${TARGETS} redisTest")
endif ()

message(STATUS --${TARGETS})
