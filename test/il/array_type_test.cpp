#include "catch.hpp"

#include "il/array_type.h"
#include "il/build_in_type.h"

TEST_CASE("array_type") {
    std::shared_ptr<runtime::il::base_type> array_elem_type = std::dynamic_pointer_cast<runtime::il::base_type>(
            std::make_shared<runtime::il::build_in_type>("char")
    );
    std::shared_ptr<runtime::il::base_type> array_length_type = std::dynamic_pointer_cast<runtime::il::base_type>(
            std::make_shared<runtime::il::build_in_type>("int")
    );
    runtime::il::array_type test{array_elem_type, array_length_type};

    SECTION("it is converted a string representation") {
        std::string const expected{"char[]"};
        auto test_str = (std::string) test;
        REQUIRE(expected == test_str);
    }

    SECTION("virtual dispatch is empty") {
        REQUIRE(test.get_virtual_dispatch().empty());
    }

    SECTION("fields contains length") {
        int constexpr expectedSize = 1;
        REQUIRE(expectedSize == test.get_fields().size());
    }

    SECTION("fields length has correct name") {
        std::string const expectedFieldName{"Length"};
        REQUIRE(expectedFieldName == test.get_fields().at(0).first);
    }

    SECTION("fields length has correct type") {
        REQUIRE(array_length_type == test.get_fields().at(0).second);
    }
}