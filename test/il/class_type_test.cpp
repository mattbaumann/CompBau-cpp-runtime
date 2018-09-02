#include "catch.hpp"

#include "il/class_type.h"

TEST_CASE("class_type") {
    runtime::il::class_type test{"TestClass"};

    SECTION("it is converted a string representation") {
        std::string const expected{"TestClass"};
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