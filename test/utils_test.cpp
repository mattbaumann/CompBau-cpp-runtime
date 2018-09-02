#include "catch.hpp"

#include "utils.h"

TEST_CASE("Test trim") {
    std::string const expected{"trimmed"};

    SECTION("Already trimmed") {
        std::string test{expected};
        runtime::trim(test);
        REQUIRE(expected == test);
    }

    SECTION("WS before") {
        std::string test{"    " + expected};
        runtime::trim(test);
        REQUIRE(expected == test);
    }

    SECTION("WS after") {
        std::string test{expected + "   "};
        runtime::trim(test);
        REQUIRE(expected == test);
    }

    SECTION("WS before and after") {
        std::string test{"    " + expected + "   "};
        runtime::trim(test);
        REQUIRE(expected == test);
    }
}