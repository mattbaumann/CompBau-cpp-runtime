#include "parser.h"
#include "../utils.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace std::literals;

namespace runtime::parser {

    void Parser::check_version(YAML::Node &root, std::shared_ptr<spdlog::logger> &logger) {
        auto version = read_attribute<int>(root, logger, "version"s, "File version tag not found");
        if (version != il_version) {
            logger->error("Unsupported intermediate file format: File version newer then runtime");
            throw UnsupportedFileFormat{"File version newer then runtime"};
        }
    }

    parser::instruction Parser::parse_instruction_with_value(YAML::const_iterator::value_type &i) {
        if (i.begin() == i.end()) {
            throw UnsupportedFileFormat{"Empty code instruction"};
        }
        auto j = *i.begin();
        auto inst_str = j.first.as<std::string>();
        auto value = j.second.as<std::string>();
        std::transform(begin(inst_str), end(inst_str), begin(inst_str),
                       [](unsigned char c) { return std::tolower(c); });
        runtime::trim(inst_str);
        parser::instruction inst{instructions.at(inst_str), value};
        return inst;
    }

    parser::instruction Parser::parse_instruction_without_value(YAML::const_iterator::value_type &i) {
        auto inst_str = i.as<std::string>();
        std::transform(inst_str.begin(), inst_str.end(), inst_str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        runtime::trim(inst_str);
        parser::instruction inst{instructions.at(inst_str)};
        return inst;
    }

    std::vector<runtime::parser::instruction> Parser::parse_code(YAML::Node code_list) {
        std::vector<runtime::parser::instruction> code{};
        std::transform(std::begin(code_list), std::end(code_list), std::back_inserter(code),
                       [&](auto &&i) {
                           return i.IsMap() ? parse_instruction_with_value(i) : parse_instruction_without_value(i);
                       });
        return code;
    }

    parser::method Parser::parse_method(YAML::const_iterator::value_type &method) {
        auto method_name = method[il_name].as<std::string>();
        auto returns_node = method[il_returns];
        auto returns = returns_node.IsDefined() and not returns_node.IsNull() ? returns_node.as<std::string>() : "void";
        auto params = method[il_params].as<std::vector<std::string>>(std::vector<std::string>{});
        auto locals = method[il_locals].as<std::vector<std::string>>(std::vector<std::string>{});
        auto code = parse_code(method[il_code]);
        return parser::method{method_name, returns, params, locals, code};
    }

    runtime::parser::class_type Parser::parse_class(YAML::Node &type, std::shared_ptr<spdlog::logger> &logger) {
        auto name = read_attribute(type, logger, il_name, il_name_error_desc);
        auto base = type[il_base].IsDefined() ? type[il_base].as<std::string>() : "";
        auto fields = type[il_fields].as<std::vector<std::string>>(std::vector<std::string>{});

        std::vector<runtime::parser::method> methods{};
        std::transform(std::begin(type[il_methods]), std::end(type[il_methods]), back_inserter(methods),
                       [&](auto &&method) { return parse_method(method); });
        return runtime::parser::class_type{name, base, fields, methods};
    }

    std::vector<runtime::parser::class_type>
    Parser::parse_types(YAML::Node &root_node, std::shared_ptr<spdlog::logger> &logger) {
        std::vector<runtime::parser::class_type> complex_types{};
        std::transform(std::begin(root_node), std::end(root_node), back_inserter(complex_types),
                       [&](auto &&type) { return parse_class(type, logger); });
        return complex_types;
    }

    std::vector<runtime::parser::class_type>
    Parser::parse_il(YAML::Node &intermediate, std::shared_ptr<spdlog::logger> &logger) {
        check_version(intermediate, logger);
        auto mainValue = read_attribute(intermediate, logger, il_main, il_main_error_desc);
        auto type_node = intermediate[il_types];
        return parse_types(type_node, logger);
    }
}
