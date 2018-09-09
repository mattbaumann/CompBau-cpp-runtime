#ifndef COMPBAU_CPP_RUNTIME_BASE_TYPE_H
#define COMPBAU_CPP_RUNTIME_BASE_TYPE_H

#include "method.h"

#include <string>
#include <vector>
#include <tuple>
#include <memory>
#include <ostream>

namespace runtime::il {
    class method;

    /**
     * @brief Base class for type descriptor objects
     *
     * Describes the types defined in the runtime system. All types may have a representation as string, the virtual
     * dispatched functions and it's field defined.
     */
    class base_type {
    public:
        explicit operator std::string() const noexcept { return to_string(); }

        virtual std::string to_string() const noexcept = 0;

        virtual std::vector<std::shared_ptr<method>> const get_virtual_dispatch() = 0;

        virtual std::vector<std::pair<std::string, std::shared_ptr<base_type>>> const get_fields() const = 0;
    };

    inline std::ostream &operator<<(std::ostream &stream, base_type const &value) {
        return stream << value.to_string();
    }

    inline std::ostream &operator<<(std::ostream &stream, std::shared_ptr<base_type> const &value) {
        return stream << value->to_string();
    }

    inline std::ostream &operator<<(std::ostream &stream, std::unique_ptr<base_type> const &value) {
        return stream << value->to_string();
    }

    inline std::ostream &operator<<(std::ostream &stream, base_type const *value) {
        return stream << value->to_string();
    }
}
#endif //COMPBAU_CPP_RUNTIME_BASE_TYPE_H
