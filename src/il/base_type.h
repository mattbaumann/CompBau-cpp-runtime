#ifndef COMPBAU_CPP_RUNTIME_BASE_TYPE_H
#define COMPBAU_CPP_RUNTIME_BASE_TYPE_H

#include <string>
#include <vector>

namespace runtime::linker {

    class base_type {
    public:
        explicit virtual operator std::string() { return "No string representation defined."; };

         
        // TODO: Add vector<method> and vector<field>
    };
}
#endif //COMPBAU_CPP_RUNTIME_BASE_TYPE_H
