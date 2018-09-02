#ifndef COMPBAU_CPP_RUNTIME_BASE_TYPE_H
#define COMPBAU_CPP_RUNTIME_BASE_TYPE_H

#include "method.h"

#include <string>
#include <vector>
#include <tuple>
#include <memory>

namespace runtime::il {

    /**
     * @brief Base class for type descriptor objects
     *
     * Describes the types defined in the runtime system. All types may have a representation as string, the virtual
     * dispatched functions and it's field defined.
     */
    class base_type {
    public:
        explicit virtual operator std::string() const = 0;

        virtual std::vector<method> const get_virtual_dispatch() const = 0;

        virtual std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const = 0;
    };
}
#endif //COMPBAU_CPP_RUNTIME_BASE_TYPE_H
