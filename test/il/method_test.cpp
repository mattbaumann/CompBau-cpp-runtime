#include "catch.hpp"

#include "il/build_in_type.h"

TEST_CASE("method descriptor") {
    std::string const method_name{ "GetName" };
    std::string const data_type{ "char" };
    auto type_ptr = std::static_pointer_cast<runtime::il::base_type>(
            std::make_shared<runtime::il::build_in_type>(data_type));

    SECTION("simple method") {
        std::string const expected{ "void " + method_name + "()" };
        runtime::il::method test{ method_name };
        REQUIRE(expected == test.to_string());
    }

    SECTION("method with return & params") {
        std::string const expected{ data_type + " " + method_name + '(' + data_type + ')' };
        runtime::il::method test{ method_name };
        test.return_type = type_ptr;
        test.parameter_types.push_back(type_ptr);
        REQUIRE(expected == (std::string) test);
    }

    SECTION("method name comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name };
        REQUIRE(test1 == test2);
    }

    SECTION("method name false comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name + "i" };
        REQUIRE_FALSE(test1 == test2);
    }

    SECTION("method return type comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name };
        test1.return_type = type_ptr;
        test2.return_type = type_ptr;
        REQUIRE(test1 == test2);
    }

    SECTION("method return type false comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name };
        test1.return_type = type_ptr;
        REQUIRE_FALSE(test1 == test2);
    }

    SECTION("method parameter type comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name };
        test1.parameter_types.push_back(type_ptr);
        test2.parameter_types.push_back(type_ptr);
        REQUIRE(test1 == test2);
    }

    SECTION("method parameter type false comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name };
        test1.parameter_types.push_back(type_ptr);
        REQUIRE_FALSE(test1 == test2);
    }

    SECTION("method parameter many type comparison") {
        runtime::il::method test1{ method_name };
        runtime::il::method test2{ method_name };
        test1.parameter_types.push_back(type_ptr);
        test1.parameter_types.push_back(type_ptr);
        test2.parameter_types.push_back(type_ptr);
        test2.parameter_types.push_back(type_ptr);
        REQUIRE(test1 == test2);
    }

    SECTION("shared_ptr method comparison") {
        auto ptr1 = std::make_shared<runtime::il::method>(method_name);
        auto ptr2 = std::make_shared<runtime::il::method>(method_name);
        REQUIRE(ptr1 == ptr2);
    }

    SECTION("shared_ptr method comparison dangling ptr") {
        auto ptr1 = std::make_shared<runtime::il::method>(method_name);
        auto ptr2 = std::make_shared<runtime::il::method>(method_name);
        ptr1.reset();
        REQUIRE_FALSE(ptr1 == ptr2);
    }

    SECTION("shared_ptr method comparison dangling ptr2") {
        auto ptr1 = std::make_shared<runtime::il::method>(method_name);
        auto ptr2 = std::make_shared<runtime::il::method>(method_name);
        ptr2.reset();
        REQUIRE_FALSE(ptr1 == ptr2);
    }
}