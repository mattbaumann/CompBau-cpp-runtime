#include "class_type.h"

#include <algorithm>

namespace runtime::il {
    std::vector<std::shared_ptr<method>> class_type::resolveOverloads() const {
        std::vector overloads{ methods };
        if (super) {
            auto above = super->resolveOverloads();
            std::copy_if(begin(above), end(above), back_inserter(overloads), [&](auto method_ptr) {
                return std::find(begin(overloads), end(overloads), method_ptr) == end(overloads);
            });
        }
        return overloads;
    }
}
