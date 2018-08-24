#ifndef COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H
#define COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H

#include "base_type.h"

namespace runtime::linker {
    class array_type : base_type {

    public:
        explicit array_type(base_type decorated_type) : decorated_type{std::move(decorated_type)} {}

    private:
        explicit operator std::string() override {
            return ((std::string) decorated_type) + "[]";
        }

    private:
        base_type decorated_type;
    };
}
#endif //COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H
