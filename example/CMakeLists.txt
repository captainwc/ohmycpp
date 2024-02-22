file(GLOB SOURCES "*.cpp")

set(EXAMPLES "[Examples]: ")

find_library(SPDLOG spdlog REQUIRED)
message(DEBUG "<spdlog> ${SPDLOG}")

foreach (file ${SOURCES})
    get_filename_component(target ${file} NAME_WE)
    add_executable(${target} ${file})
    target_include_directories(${target} PUBLIC ${INCLUDE_DIR})
    # target_link_libraries(${target} PUBLIC ${SPDLOG})
    set(EXAMPLES ${EXAMPLES} ${target})
endforeach ()

message(STATUS ${EXAMPLES})