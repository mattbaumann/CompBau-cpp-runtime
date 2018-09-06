#include "catch.hpp"

#include "utils.h"

#include <iostream>

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

struct join_test_class {
    std::string value;
};

std::ostream &operator<<(std::ostream &stream, join_test_class const &value) {
    stream << value.value;
    return stream;
}

TEST_CASE("string join") {
    SECTION("empty join") {
        std::vector<std::string> test{};
        REQUIRE(runtime::join(begin(test), end(test), ", ").empty());
    }

    SECTION("one value") {
        std::string expected = "one";
        std::vector<std::string> test{expected};
        REQUIRE(expected == runtime::join(begin(test), end(test), ", "));
    }

    SECTION("many values") {
        std::string const expected{"a word with lot of meaning"};
        auto test = std::vector<std::string>{"a", "word", "with", "lot", "of", "meaning"};
        REQUIRE(expected == runtime::join(begin(test), end(test), " "));
    }

    SECTION("class behaviour") {
        std::string const expected{"test, class"};
        std::vector<join_test_class> test{join_test_class{"test"}, join_test_class{"class"}};
        REQUIRE(expected == runtime::join(begin(test), end(test), ", "));
    }
}
