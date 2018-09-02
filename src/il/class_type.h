#ifndef COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
#define COMPBAU_CPP_RUNTIME_CLASS_TYPE_H

#include "base_type.h"

#include <string>

namespace runtime::il {
    class class_type : public base_type {
    public:
        explicit class_type(std::string name) : name(std::move(name)) {}

        explicit operator std::string() const override {
            return name;
        }

        std::vector<method> const get_virtual_dispatch() const override {
            return std::vector<method>{};
        }

        std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const override {
            return std::vector<std::pair<std::string, std::shared_ptr<base_type>>>{};
        }

    private:
        std::string name;
        std::vector<method> methods{};
        std::vector<base_type> fields{};
    };
}

#endif //COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
