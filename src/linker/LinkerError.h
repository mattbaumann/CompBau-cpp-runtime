#ifndef COMPBAU_CPP_RUNTIME_LINKERERROR_H
#define COMPBAU_CPP_RUNTIME_LINKERERROR_H

#include <stdexcept>

namespace runtime::linker {
    struct LinkerError : std::logic_error {
        explicit LinkerError(const char *what) : logic_error(what) {}

        explicit LinkerError(const std::string &what) : logic_error(what) {}
    };
}

#endif //COMPBAU_CPP_RUNTIME_LINKERERROR_H
