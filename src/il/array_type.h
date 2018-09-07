#ifndef COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H
#define COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H

#include "base_type.h"

#include <string>
#include <tuple>

namespace runtime::il {
    class array_type : public base_type {

        std::string const length_field_name{"Length"};

    public:
        explicit array_type(std::shared_ptr<base_type> decorated_type, std::shared_ptr<base_type> int_type) :
                decorated_type{std::move(decorated_type)}, int_type{std::move(int_type)} {}

        std::string to_string() const noexcept override {
            return decorated_type->to_string() + "[]";
        }

        std::vector<method> const get_virtual_dispatch() const override {
            return std::vector<method>{};
        }

        std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const override {
            return std::vector({std::pair{length_field_name, int_type}});
        }

    private:
        std::shared_ptr<base_type> const decorated_type;
        std::shared_ptr<base_type> const int_type;
    };
}
#endif //COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H
