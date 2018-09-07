#ifndef COMPBAU_CPP_RUNTIME_IL_METHOD_H
#define COMPBAU_CPP_RUNTIME_IL_METHOD_H

#include "instruction.h"
#include "base_type.h"

#include <vector>
#include <string>
#include <memory>

namespace runtime::il {
    class base_type;

    struct method {
        std::string name;
        std::shared_ptr<base_type> return_type{};
        std::vector<std::shared_ptr<base_type>> parameter_types{};
        std::vector<std::shared_ptr<base_type>> local_types{};
        std::vector<instruction> code{};

        explicit method(std::string name) : name{std::move(name)} {}

        explicit operator std::string() const noexcept { return to_string(); }

        std::string to_string() const noexcept;
    };

    inline bool operator==(method const &left, method const &right) noexcept {
        return left.to_string() == right.to_string();
    }

    inline bool operator!=(method const &left, method const &right) noexcept { return !(left == right); }
}

#endif //COMPBAU_CPP_RUNTIME_METHOD_H
