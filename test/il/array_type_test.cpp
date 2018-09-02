#include "catch.hpp"

#include "il/array_type.h"
#include "il/build_in_type.h"

TEST_CASE("array_type") {
    std::shared_ptr<runtime::il::base_type> ptr{new runtime::il::build_in_type{"char"}};
    runtime::il::array_type test{ptr};

    SECTION("it is converted a string representation") {
        std::string const expected{"char[]"};
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