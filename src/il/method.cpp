#include "method.h"
#include "utils.h"

std::string runtime::il::method::to_string() const noexcept {
    std::ostringstream result{};
    std::vector<std::string> parameter_names{};
    std::transform(begin(parameter_types), end(parameter_types), back_inserter(parameter_names),
                   [&](auto type) { return type->to_string(); });
    result << (return_type ? return_type->to_string() : "void") << " ";
    result << name << "(" << join(begin(parameter_names), end(parameter_names), ", ") << ")";
    return result.str();
}
