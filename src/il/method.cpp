#include "method.h"
#include "utils.h"
#include "base_type.h"

std::string runtime::il::method::to_string() const noexcept {
    std::ostringstream result{};
    result << (return_type ? return_type->to_string() : "void") << " ";
    result << name << "(" << join(begin(parameter_types), end(parameter_types), ", ") << ")";
    return result.str();
}
