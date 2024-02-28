file(GLOB SOURCES "*.cpp")

set(TARGETS "[Tests]: ")

find_library(REDIS hiredis REQUIRED)

foreach(file ${SOURCES})
    get_filename_component(target ${file} NAME_WE)
    add_executable(${target} ${file})
    target_include_directories(${target} PUBLIC ${INCLUDE_DIR})
    target_link_libraries(${target} PUBLIC ${REDIS})
    set(TARGETS "${TARGETS} ${target}")
endforeach()

message(STATUS --${TARGETS})
