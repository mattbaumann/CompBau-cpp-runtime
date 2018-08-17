#include "catch.hpp"
#include "parser/parser.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/null_sink.h>

TEST_CASE("empty input file") {
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
    auto logger = std::make_shared<spdlog::logger>("null-logger", null_sink);

    runtime::parser::Parser parser{};

    SECTION("empty input file") {
        YAML::Node node = YAML::Load("");
        REQUIRE_THROWS_AS(parser.parse_il(node, logger), runtime::parser::UnsupportedFileFormat);
    }

    SECTION("no version node") {
        YAML::Node node = YAML::Load("{intermediate: 1}");
        REQUIRE_THROWS_AS(parser.parse_il(node, logger), runtime::parser::UnsupportedFileFormat);
    }

    SECTION("too new file") {
        YAML::Node node = YAML::Load("{version: 2}");
        REQUIRE_THROWS_AS(parser.parse_il(node, logger), runtime::parser::UnsupportedFileFormat);
    }

    SECTION("correct version and main") {
        YAML::Node node = YAML::Load("{version: 1, main: myfunc}");
        REQUIRE_NOTHROW(parser.parse_il(node, logger));
    }
}

TEST_CASE("check version") {
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
    std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("null-logger", null_sink);

    runtime::parser::Parser parser{};

    SECTION("No version tag") {
        YAML::Node node = YAML::Load("{}");
        REQUIRE_THROWS_AS(parser.parse_il(node, logger), runtime::parser::UnsupportedFileFormat);
    }

    SECTION("version tag too high") {
        YAML::Node node = YAML::Load("{version: 2}");
        REQUIRE_THROWS_AS(parser.parse_il(node, logger), runtime::parser::UnsupportedFileFormat);
    }

    SECTION("version tag correct") {
        YAML::Node node = YAML::Load("{version: 1}");
        REQUIRE_THROWS_AS(parser.parse_il(node, logger), runtime::parser::UnsupportedFileFormat);
    }
}

TEST_CASE("parse instruction without value") {
    runtime::parser::Parser parser{};

    SECTION("correct instruction syntax") {
        YAML::Node node = YAML::Load("[ret]");
        REQUIRE_NOTHROW(parser.parse_instruction_without_value(*node.begin()));
    }

    SECTION("correct parsing") {
        YAML::Node node = YAML::Load("[ret]");
        auto instruction = parser.parse_instruction_without_value(*node.begin());
        REQUIRE(runtime::parser::instruction_code::ret == instruction.code);
    }

    SECTION("case-insensitive parsing") {
        YAML::Node node = YAML::Load("[CaStclAss]");
        auto instruction = parser.parse_instruction_without_value(*node.begin());
        REQUIRE(runtime::parser::instruction_code::castclass == instruction.code);
    }
}

TEST_CASE("parse instruction with value") {
    runtime::parser::Parser parser{};

    SECTION("correct instruction syntax") {
        YAML::Node node = YAML::Load("[{ldc_s: str}]");
        REQUIRE_NOTHROW(parser.parse_instruction_with_value(*node.begin()));
    }

    SECTION("correct parsing") {
        YAML::Node node = YAML::Load("[{ldc_s: str}]");
        runtime::parser::instruction instruction = parser.parse_instruction_with_value(*node.begin());
        REQUIRE(runtime::parser::instruction_code::ldc_s == instruction.code);
    }

    SECTION("correct value") {
        YAML::Node node = YAML::Load("[{ldc_s: str}]");
        runtime::parser::instruction instruction = parser.parse_instruction_with_value(*node.begin());
        REQUIRE("str" == instruction.argument);
    }

    SECTION("case-insensitive parsing") {
        YAML::Node node = YAML::Load("[{CaStClasS: str}]");
        runtime::parser::instruction instruction = parser.parse_instruction_with_value(*node.begin());
        REQUIRE(runtime::parser::instruction_code::castclass == instruction.code);
    }
}

TEST_CASE("parse code") {
    runtime::parser::Parser parser{};

    SECTION("empty code block") {
        YAML::Node node = YAML::Load("[]");
        std::vector<runtime::parser::instruction> instructions = parser.parse_code(node);
        REQUIRE(instructions.empty());
    }

    SECTION("code without value") {
        YAML::Node node = YAML::Load("[ret, ret]");
        auto expected = std::vector{
                runtime::parser::instruction{runtime::parser::instruction_code::ret},
                runtime::parser::instruction{runtime::parser::instruction_code::ret}
        };
        std::vector<runtime::parser::instruction> instructions = parser.parse_code(node);
        REQUIRE(expected == instructions);
    }

    GIVEN("code with value") {
        YAML::Node node = YAML::Load("[ldc_i: 0, ldc_s: uno]");
        auto expected = std::vector{
                runtime::parser::instruction{runtime::parser::instruction_code::ldc_i, "0"},
                runtime::parser::instruction{runtime::parser::instruction_code::ldc_s, "uno"}
        };
        std::vector<runtime::parser::instruction> instructions = parser.parse_code(node);
        REQUIRE(expected == instructions);
    }

    GIVEN("mixed code with/out values") {
        YAML::Node node = YAML::Load("[ldc_i: 0, ret, ldc_s: uno]");
        auto expected = std::vector{
                runtime::parser::instruction{runtime::parser::instruction_code::ldc_i, "0"},
                runtime::parser::instruction{runtime::parser::instruction_code::ret},
                runtime::parser::instruction{runtime::parser::instruction_code::ldc_s, "uno"}
        };
        std::vector<runtime::parser::instruction> instructions = parser.parse_code(node);
        REQUIRE(expected == instructions);
    }
}

TEST_CASE("parse method") {
    runtime::parser::Parser parser{};

    SECTION("method without code") {
        YAML::Node node = YAML::Load("[{name: Main}]");
        runtime::parser::method expected{"Main", "void", std::vector<std::string>{}, std::vector<std::string>{},
                                         std::vector<runtime::parser::instruction>{}};
        auto method = parser.parse_method(*node.begin());
        REQUIRE(expected == method);
    }

    SECTION("simple method definition") {
        YAML::Node node = YAML::Load("[{name: Main, params: [-1], returns: 1, locals: [-2], code: [ret]}]");
        runtime::parser::method expected{"Main", "1", std::vector<std::string>{"-1"}, std::vector<std::string>{"-2"},
                                         std::vector{
                                                 runtime::parser::instruction{runtime::parser::instruction_code::ret}}};
        REQUIRE(expected == parser.parse_method(*node.begin()));
    }
}

TEST_CASE("parse class") {
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
    std::shared_ptr<spdlog::logger> logger = std::make_shared<spdlog::logger>("null-logger", null_sink);

    runtime::parser::Parser parser{};

    SECTION("empty class") {
        YAML::Node node = YAML::Load("{name: MainClass, fields: [-1]}");
        runtime::parser::class_type expected{"MainClass", "", std::vector<std::string>{"-1"},
                                             std::vector<runtime::parser::method>{}};
        auto class_descriptor = parser.parse_class(node, logger);
        REQUIRE(expected == class_descriptor);
    }
}