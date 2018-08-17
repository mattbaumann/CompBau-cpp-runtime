#ifndef COMPBAU_CPP_RUNTIME_UNSUPPORTEDFILEEXCEPTION_H
#define COMPBAU_CPP_RUNTIME_UNSUPPORTEDFILEEXCEPTION_H

#include <stdexcept>

namespace runtime::parser {
    struct UnsupportedFileFormat : std::logic_error {
        explicit UnsupportedFileFormat(const char *what) : logic_error(what) {}

        explicit UnsupportedFileFormat(const std::string &what) : logic_error(what) {}
    };
}

#endif //COMPBAU_CPP_RUNTIME_UNSUPPORTEDFILEEXCEPTION_H
