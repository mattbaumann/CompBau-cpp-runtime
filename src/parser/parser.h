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
                {"ldc_b",     runtime::il::instruction_code::ldc_b},
                {"ldc_c",     runtime::il::instruction_code::ldc_c},
                {"ldc_i",     runtime::il::instruction_code::ldc_i},
                {"ldc_s",     runtime::il::instruction_code::ldc_s},
                {"ldnull",    runtime::il::instruction_code::ldnull},
                {"br",        runtime::il::instruction_code::br},
                {"brtrue",    runtime::il::instruction_code::brtrue},
                {"brfalse",   runtime::il::instruction_code::brfalse},
                {"neg",       runtime::il::instruction_code::neg},
                {"add",       runtime::il::instruction_code::add},
                {"sub",       runtime::il::instruction_code::sub},
                {"mul",       runtime::il::instruction_code::mul},
                {"div",       runtime::il::instruction_code::div},
                {"mod",       runtime::il::instruction_code::mod},
                {"clt",       runtime::il::instruction_code::clt},
                {"cle",       runtime::il::instruction_code::cle},
                {"cgt",       runtime::il::instruction_code::cgt},
                {"cge",       runtime::il::instruction_code::cge},
                {"ceq",       runtime::il::instruction_code::ceq},
                {"cne",       runtime::il::instruction_code::cne},
                {"ldloc",     runtime::il::instruction_code::ldloc},
                {"stloc",     runtime::il::instruction_code::stloc},
                {"ldarg",     runtime::il::instruction_code::ldarg},
                {"starg",     runtime::il::instruction_code::starg},
                {"ldfld",     runtime::il::instruction_code::ldfld},
                {"stfld",     runtime::il::instruction_code::stfld},
                {"newarr",    runtime::il::instruction_code::newarr},
                {"ldlen",     runtime::il::instruction_code::ldlen},
                {"ldelem",    runtime::il::instruction_code::ldelem},
                {"stelem",    runtime::il::instruction_code::stelem},
                {"call",      runtime::il::instruction_code::call},
                {"newobj",    runtime::il::instruction_code::newobj},
                {"ldthis",    runtime::il::instruction_code::ldthis},
                {"callvirt",  runtime::il::instruction_code::callvirt},
                {"isinst",    runtime::il::instruction_code::isinst},
                {"castclass", runtime::il::instruction_code::castclass},
                {"ret",       runtime::il::instruction_code::ret}
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
