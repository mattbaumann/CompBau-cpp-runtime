#include "catch.hpp"

#include "il/build_in_type.h"

TEST_CASE("method descriptor") {
    SECTION("simple method") {
        std::string const expected{"void GetName()"};
        runtime::il::method test{"GetName"};
        REQUIRE(expected == test.to_string());
    }

    SECTION("method with return & params") {
        std::string const expected{"char GetName(char)"};
        runtime::il::method test{"GetName"};
        auto type_ptr = std::static_pointer_cast<runtime::il::base_type>(
                std::make_shared<runtime::il::build_in_type>("char"));
        test.return_type = type_ptr;
        test.parameter_types.push_back(type_ptr);
        REQUIRE(expected == (std::string) test);
    }
}