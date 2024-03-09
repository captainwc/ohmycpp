set(TARGETS "[Examples]: ")

set(COMMON_TEST main.cpp)

foreach (test_file ${COMMON_TEST})
    STRING(REGEX REPLACE ".cpp" "" target ${test_file})
    add_executable(${target} ${test_file})
    target_include_directories(${target} PUBLIC ${INCLUDE_DIR})
    set(TARGETS "${TARGETS} ${target}")
endforeach ()

if (${SYSTEM} STREQUAL "unix")
    add_executable(spdlogEg spdlogEg.cpp)
    target_include_directories(spdlogEg.cpp PUBLIC ${INCLUDE_DIR})
    set(TARGETS "${TARGETS} spdlogEg")
endif ()

message(STATUS --${TARGETS})