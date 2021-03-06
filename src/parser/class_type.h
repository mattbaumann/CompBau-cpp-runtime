#ifndef COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
#define COMPBAU_CPP_RUNTIME_CLASS_TYPE_H

#include "method.h"

#include <string>
#include <vector>

namespace runtime::parser {

    struct class_type {

        class_type(std::string name, std::string base, std::vector<std::string> field_types,
                   std::vector<method> methods)
                : name{std::move(name)}, base{std::move(base)}, field_types(std::move(field_types)),
                  methods(std::move(methods)) {}

        std::string name;
        std::string base;
        std::vector<std::string> const field_types;
        std::vector<runtime::parser::method> const methods;

        bool operator==(class_type const &rhs) const {
            return name == rhs.name and
                   base == rhs.base and
                   field_types == rhs.field_types and
                   methods == rhs.methods;
        }

        bool operator!=(class_type const &rhs) const {
            return !(rhs == *this);
        }
    };
}


#endif //COMPBAU_CPP_RUNTIME_TYPE_H
