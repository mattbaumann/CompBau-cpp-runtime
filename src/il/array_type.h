#ifndef COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H
#define COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H

#include "base_type.h"

namespace runtime::il {
    class array_type : public base_type {

    public:
        explicit array_type(std::shared_ptr<base_type> decorated_type) : decorated_type{std::move(decorated_type)} {}

        explicit operator std::string() const override {
            return ((std::string) *decorated_type) + "[]";
        }

        std::vector<method> const get_virtual_dispatch() const override {
            return std::vector<method>();
        }

        std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const override {
            return std::vector<std::pair<std::string, std::shared_ptr<base_type>>>();
        }

    private:
        std::shared_ptr<base_type> decorated_type;
    };
}
#endif //COMPBAU_CPP_RUNTIME_ARRAY_TYPE_H
