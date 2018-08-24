#ifndef COMPBAU_CPP_RUNTIME_RUNTIME_H
#define COMPBAU_CPP_RUNTIME_RUNTIME_H

#include "il/instruction_code.h"
#include "UnsupportedFileFormat.h"
#include "method.h"
#include "class_type.h"
#include "parser_model.h"

#include <yaml-cpp/yaml.h>

#include <spdlog/logger.h>

#include <vector>
#include <memory>
#include <map>

namespace runtime::parser {

    class Parser {
        static int constexpr il_version = 1;
        std::string const il_code{"code"};
        std::string const il_name{"name"};
        std::string const il_name_error_desc{"Class name was undefined"};
        std::string const il_fields{"fields"};
        std::string const il_returns{"returns"};
        std::string const il_params{"params"};
        std::string const il_locals{"locals"};
        std::string const il_methods{"methods"};
        std::string const il_main{"main"};
        std::string const il_main_error_desc{"Main function not found"};
        std::string const il_types{"types"};
        std::string const il_base{"base"};

        /// \brief parsing map for instruction codes
        const std::map<std::string, runtime::il::instruction_code> instructions = {
                {"ldc_b",     parser::instruction_code::ldc_b},
                {"ldc_c",     parser::instruction_code::ldc_c},
                {"ldc_i",     parser::instruction_code::ldc_i},
                {"ldc_s",     parser::instruction_code::ldc_s},
                {"ldnull",    parser::instruction_code::ldnull},
                {"br",        parser::instruction_code::br},
                {"brtrue",    parser::instruction_code::brtrue},
                {"brfalse",   parser::instruction_code::brfalse},
                {"neg",       parser::instruction_code::neg},
                {"add",       parser::instruction_code::add},
                {"sub",       parser::instruction_code::sub},
                {"mul",       parser::instruction_code::mul},
                {"div",       parser::instruction_code::div},
                {"mod",       parser::instruction_code::mod},
                {"clt",       parser::instruction_code::clt},
                {"cle",       parser::instruction_code::cle},
                {"cgt",       parser::instruction_code::cgt},
                {"cge",       parser::instruction_code::cge},
                {"ceq",       parser::instruction_code::ceq},
                {"cne",       parser::instruction_code::cne},
                {"ldloc",     parser::instruction_code::ldloc},
                {"stloc",     parser::instruction_code::stloc},
                {"ldarg",     parser::instruction_code::ldarg},
                {"starg",     parser::instruction_code::starg},
                {"ldfld",     parser::instruction_code::ldfld},
                {"stfld",     parser::instruction_code::stfld},
                {"newarr",    parser::instruction_code::newarr},
                {"ldlen",     parser::instruction_code::ldlen},
                {"ldelem",    parser::instruction_code::ldelem},
                {"stelem",    parser::instruction_code::stelem},
                {"call",      parser::instruction_code::call},
                {"newobj",    parser::instruction_code::newobj},
                {"ldthis",    parser::instruction_code::ldthis},
                {"callvirt",  parser::instruction_code::callvirt},
                {"isinst",    parser::instruction_code::isinst},
                {"castclass", parser::instruction_code::castclass},
                {"ret",       parser::instruction_code::ret}
        };

    public:

        template<typename T = std::string>
        T read_attribute(YAML::Node &root, std::shared_ptr<spdlog::logger> &logger, std::string const &name,
                         std::string const &ex_text) {
            if (not root[name].IsDefined()) {
                logger->error("Required attribute not found, " + ex_text);
                throw UnsupportedFileFormat{ex_text};
            }
            return root[name].as<T>();
        }

        /// \brief A factory that will read the intermediate language file and build a runtime-object from the code.
        parser_model
        parse_il(YAML::Node &intermediate, std::shared_ptr<spdlog::logger> &logger);

        void check_version(YAML::Node &root, std::shared_ptr<spdlog::logger> &logger);

        runtime::il::instruction parse_instruction_with_value(YAML::const_iterator::value_type &i);

        runtime::il::instruction parse_instruction_without_value(YAML::const_iterator::value_type &i);

        std::vector<runtime::il::instruction> parse_code(YAML::Node method);

        parser::method parse_method(YAML::const_iterator::value_type &method);

        std::vector<runtime::parser::class_type> parse_types(YAML::Node &root_node,
                                                             std::shared_ptr<spdlog::logger> &logger);

        runtime::parser::class_type parse_class(YAML::Node &type, std::shared_ptr<spdlog::logger> &logger);
    };

}

#endif //COMPBAU_CPP_RUNTIME_RUNTIME_H
