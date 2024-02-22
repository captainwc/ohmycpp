find_library(GTEST gtest)
if(GTEST)
    message(DEBUG <GTEST>:${GTEST})
endif()

find_library(PTHREAD pthread REQUIRED)
