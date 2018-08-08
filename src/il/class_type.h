#ifndef COMPBAU_CPP_RUNTIME_TYPE_H
#define COMPBAU_CPP_RUNTIME_TYPE_H

#include "method.h"

#include <string>

namespace runtime::il {

    struct class_type {
        std::string name;
        class_type base;
        std::vector<int> field_types;
        std::vector<runtime::il::method> methods;
    };
}


#endif //COMPBAU_CPP_RUNTIME_TYPE_H
