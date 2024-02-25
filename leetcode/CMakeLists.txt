add_subdirectory(hash)
add_subdirectory(linerlist)
add_subdirectory(str)
add_subdirectory(search)

option(BUILD_LEETCODE ON)
if(BUILD_LEETCODE)
    add_subdirectory(solutions)
endif()
