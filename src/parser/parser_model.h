#ifndef COMPBAU_CPP_RUNTIME_PARSER_MODEL_H
#define COMPBAU_CPP_RUNTIME_PARSER_MODEL_H

#include "class_node.h"

#include <vector>
#include <string>

namespace runtime::parser {

    struct parser_model {
        std::string main_method;
        std::vector<class_node> classes;

        parser_model(std::string main_method, std::vector<class_node> classes) :
                main_method(std::move(main_method)),
                classes(std::move(classes)) {}

        bool operator==(parser_model const &rhs) const {
            return main_method == rhs.main_method &&
                   classes == rhs.classes;
        }

        bool operator!=(parser_model const &rhs) const {
            return !(rhs == *this);
        }
    };
}

#endif //COMPBAU_CPP_RUNTIME_PARSER_MODEL_H
