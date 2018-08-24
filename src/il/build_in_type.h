#ifndef COMPBAU_CPP_RUNTIME_BUILD_IN_TYPE_H
#define COMPBAU_CPP_RUNTIME_BUILD_IN_TYPE_H

#include "base_type.h"

#include <string>

namespace runtime::linker {
    class build_in_type : base_type {

    public:
        explicit build_in_type(std::string name) : name(std::move(name)) {}

    private:
        explicit operator std::string() override {
            return name;
        }

    private:
        std::string const name;
    };
}

#endif //COMPBAU_CPP_RUNTIME_BUILD_IN_TYPE_H
