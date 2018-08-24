#ifndef COMPBAU_CPP_RUNTIME_CLASSVISITOR_H
#define COMPBAU_CPP_RUNTIME_CLASSVISITOR_H

#include "parser/parse_tree_visitor.h"
#include "base_type.h"

#include <map>
#include <string>
#include <memory>

namespace runtime::linker {
    class class_visitor : runtime::parser::parse_tree_visitor {

    public:
        class_visitor(std::shared_ptr<std::map<std::string, base_type>> const &type_cache) : type_cache(type_cache) {}

    private:
        void visitClass(parser::class_type const &classType) override {

        }

    private:

        std::shared_ptr<std::map<std::string, base_type>> const type_cache;
    };
}

#endif //COMPBAU_CPP_RUNTIME_CLASSVISITOR_H
