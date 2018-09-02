#ifndef COMPBAU_CPP_RUNTIME_BUILD_IN_TYPE_H
#define COMPBAU_CPP_RUNTIME_BUILD_IN_TYPE_H

#include "base_type.h"
#include "method.h"

#include <string>

namespace runtime::il {
    class build_in_type : public base_type {

    public:
        explicit build_in_type(std::string name) : name{std::move(name)} {}

        explicit operator std::string() const override {
            return name;
        }

        std::vector<method> const get_virtual_dispatch() const override;

        std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const override;

    private:
        std::string const name;
    };
}

#endif //COMPBAU_CPP_RUNTIME_BUILD_IN_TYPE_H
