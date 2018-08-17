#ifndef COMPBAU_CPP_RUNTIME_LINKERERROR_H
#define COMPBAU_CPP_RUNTIME_LINKERERROR_H

#include <stdexcept>

namespace runtime::linker {
    struct linker_error : std::logic_error {
        explicit linker_error(const char *what) : logic_error(what) {}

        explicit linker_error(const std::string &what) : logic_error(what) {}
    };
}

#endif //COMPBAU_CPP_RUNTIME_LINKERERROR_H
