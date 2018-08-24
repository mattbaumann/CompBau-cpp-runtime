#ifndef COMPBAU_CPP_RUNTIME_METHOD_H
#define COMPBAU_CPP_RUNTIME_METHOD_H

#include "il/instruction_code.h"
#include "il/instruction.h"

#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/any.hpp>

namespace runtime::parser {
    struct method {
        std::string name;
        std::string returns;
        std::vector<std::string> params;
        std::vector<std::string> locals;
        std::vector<runtime::il::instruction> code;

        method(std::string name, std::string returns, std::vector<std::string> params,
               std::vector<std::string> locals, std::vector<runtime::il::instruction> code)
                : name{std::move(name)}, returns{std::move(returns)}, params{std::move(params)},
                  locals{std::move(locals)}, code{std::move(code)} {}

        bool operator==(const method &rhs) const {
            return name == rhs.name and
                   returns == rhs.returns and
                   params == rhs.params and
                   locals == rhs.locals and
                   code == rhs.code;
        }

        bool operator!=(const method &rhs) const {
            return !(rhs == *this);
        }
    };
}

#endif //COMPBAU_CPP_RUNTIME_METHOD_H
