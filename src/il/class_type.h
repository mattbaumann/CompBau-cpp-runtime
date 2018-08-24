#ifndef COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
#define COMPBAU_CPP_RUNTIME_CLASS_TYPE_H

#include "base_type.h"

#include <string>

namespace runtime::linker {
    class class_type : base_type {
    public:
        explicit class_type(std::string name) : name(std::move(name)) {}

    private:

        explicit operator std::string() override {
            return name;
        }

        // TODO: Add vector<method> with the overrides applied to method calls

    private:
        std::string name;
    };
}

#endif //COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
