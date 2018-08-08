#ifndef COMPBAU_CPP_RUNTIME_METHOD_H
#define COMPBAU_CPP_RUNTIME_METHOD_H

#include "instruction_code.h"

#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/any.hpp>

namespace runtime::il {
    struct method {
        std::string name;
        boost::optional<int> returns;
        std::vector<int> params;
        std::vector<int> locals;
        std::vector<std::tuple<instruction_code, boost::any>> code;
    };
}

#endif //COMPBAU_CPP_RUNTIME_METHOD_H
