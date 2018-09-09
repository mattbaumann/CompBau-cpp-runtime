#ifndef COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
#define COMPBAU_CPP_RUNTIME_CLASS_TYPE_H

#include "base_type.h"

#include <string>

namespace runtime::il {
    class class_type : public base_type {
    public:
        std::string const name;
        std::shared_ptr<class_type> super{ };
        std::vector<std::shared_ptr<method>> methods{ };
        std::vector<std::shared_ptr<base_type>> fields{ };

        explicit class_type(std::string name) : name(std::move(name)) {}

        // This function is bottom case of method -> class_type recursion, do not call functions here.
        std::string to_string() const noexcept override {
            return name;
        }

        std::vector<std::shared_ptr<method>> const get_virtual_dispatch() override {
            if (not DT_calculated) {
                dispatch_table = resolveOverloads();
                DT_calculated = true;
            }
            return dispatch_table;
        }

        std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const override {
            return std::vector<std::pair<std::string, std::shared_ptr<base_type>>>{};
        }

    private:
        std::vector<std::shared_ptr<method>> resolveOverloads() const;

        std::vector<std::shared_ptr<method>> dispatch_table{ };
        bool DT_calculated = false;
    };
}

#endif //COMPBAU_CPP_RUNTIME_CLASS_TYPE_H
