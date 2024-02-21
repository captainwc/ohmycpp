file(GLOB SOURCES "*.cpp")

set(EXAMPLES "[Examples]: ")

foreach (file ${SOURCES})
    get_filename_component(target ${file} NAME_WE)
    add_executable(${target} ${file})
    target_include_directories(${target} PUBLIC ${INCLUDE_DIR})
    set(EXAMPLES ${EXAMPLES} ${target})
endforeach ()

message(STATUS ${EXAMPLES})