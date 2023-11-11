#include "algorithm/Utils.h"
#define DOCTEST
#include "common.h"

TEST_CASE("string") {
    SUBCASE("split string") {
        std::string str = "1,2,3,4,5,6";
        CHECK_EQ("[1,2,3,4,5,6]",vector2String(splitString(str, ",")));
    }
}