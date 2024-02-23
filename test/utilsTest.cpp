#include "utils.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Utils Test") {
    SUBCASE("split string") {
        auto ret = split("hello, world! ", ',');
        CHECK_EQ(2, ret.size());
    }
    
    SUBCASE("format string") {
        auto ret = format_string("hello the {} world {} haha", "beautiful", "!");
        CHECK_EQ(ret, "hello the beautiful world ! haha");
    }
}