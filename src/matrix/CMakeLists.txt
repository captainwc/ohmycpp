set(SOURCES
    146.cpp
        )

include_directories(../../include)

foreach (file ${SOURCES})
    string(REGEX REPLACE ".cpp$" "" target_name ${file})
    add_executable(${target_name} ${file})
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/../include)
endforeach ()