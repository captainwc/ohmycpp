set(COMMON_TEST graphicTest.cpp lctest.cpp utilsTest.cpp)

add_targets("Test" ${COMMON_TEST})

# if(LIB_REDIS)
#     add_executable(redisTest redisTest.cpp)
#     target_include_directories(${redisTest} PRIVATE ${INCLUDE_DIR})
#     target_link_libraries(${redisTest} PRIVATE ${LIB_REDIS})
# endif()
