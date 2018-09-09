#include "catch.hpp"

#include "il/class_type.h"
#include "il/build_in_type.h"

TEST_CASE("empty class_type") {
    runtime::il::class_type test{"TestClass"};

    SECTION("string convertion operator") {
        std::string const expected{ "TestClass" };
        REQUIRE(expected == (std::string) test);
    }

    SECTION("to_string() method") {
        std::string const expected{"TestClass"};
        REQUIRE(expected == test.to_string());
    }

    SECTION("virtual dispatch is empty") {
        REQUIRE(test.get_virtual_dispatch().empty());
    }

    SECTION("fields is empty") {
        REQUIRE(test.get_fields().empty());
    }
}

TEST_CASE("overloading") {
    std::string const class_name{ "TestClass" };
    std::string const method_name{ "GetName" };
    std::string const data_type{ "char" };
    auto type_ptr = std::static_pointer_cast<runtime::il::base_type>(
            std::make_shared<runtime::il::build_in_type>(data_type));

    SECTION("empty class") {
        runtime::il::class_type test{ class_name };
        REQUIRE(test.get_virtual_dispatch().empty());
    }

    SECTION("VD finds duplicates") {
        constexpr int expectedSize = 1;
        runtime::il::class_type test{ class_name };
        auto super = std::make_shared<runtime::il::class_type>("Super" + class_name);
        test.super = super;
        auto super_method = std::make_shared<runtime::il::method>(method_name);
        super_method->return_type = type_ptr;
        super_method->parameter_types.push_back(type_ptr);
        super->methods.push_back(super_method);
        test.methods.push_back(super_method);
        REQUIRE(expectedSize == test.get_virtual_dispatch().size());
    }

    SECTION("VD separates functions") {
        constexpr int expectedSize = 2;
        runtime::il::class_type test{ class_name };
        auto super = std::make_shared<runtime::il::class_type>("Super" + class_name);
        test.super = super;
        auto super_method = std::make_shared<runtime::il::method>(method_name);
        super_method->return_type = type_ptr;
        super_method->parameter_types.push_back(type_ptr);
        auto unrelated = std::make_shared<runtime::il::method>(method_name);
        unrelated->return_type = type_ptr;
        super->methods.push_back(super_method);
        test.methods.push_back(unrelated);
        REQUIRE(expectedSize == test.get_virtual_dispatch().size());
    }
}