#ifndef COMPBAU_CPP_RUNTIME_INSTRUCTION_H
#define COMPBAU_CPP_RUNTIME_INSTRUCTION_H

#include "instruction_code.h"

#include <string>

namespace runtime::parser {

    struct instruction {
        instruction_code code;
        std::string argument;

        explicit instruction(instruction_code code) : code{code}, argument{} {}

        instruction(instruction_code code, std::string arg) : code{code}, argument{std::move(arg)} {}

        bool operator==(const instruction &rhs) const {
            return code == rhs.code and argument == rhs.argument;
        }

        bool operator!=(const instruction &rhs) const {
            return !(*this == rhs);
        }
    };
}

#endif //COMPBAU_CPP_RUNTIME_INSTRUCTION_H
