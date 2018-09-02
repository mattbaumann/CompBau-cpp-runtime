#include "catch.hpp"

#include "il/build_in_type.h"

TEST_CASE("base_type") {
    runtime::il::build_in_type test{"char"};

    SECTION("it is converted a string representation") {
        std::string const expected{"char"};
        auto test_str = (std::string) test;
        REQUIRE(expected == test_str);
    }

    SECTION("virtual dispatch is empty") {
        REQUIRE(test.get_virtual_dispatch().empty());
    }

    SECTION("fields is empty") {
        REQUIRE(test.get_fields().empty());
    }
}