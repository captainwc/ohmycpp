file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(file ${SOURCES})
    string(REPLACE ".cpp" "" target_name ${file})
    add_executable(${target_name} ${file})
    set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/../include)
    install(TARGETS ${target_name} DESTINATION ~/test/cmake)
endforeach(file ${SOURCES})
