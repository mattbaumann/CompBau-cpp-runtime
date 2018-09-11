#ifndef COMPBAU_CPP_RUNTIME_PARSER_VISITOR_H
#define COMPBAU_CPP_RUNTIME_PARSER_VISITOR_H

#include "class_node.h"
#include "parser_model.h"
#include "method.h"
#include "il/instruction.h"

namespace runtime::parser {

    class parse_tree_visitor {

        virtual void visitModel(parser_model const &model) {
            for (auto const &i : model.classes) {
                visitClass(i);
            }
        }

        virtual void visitClass(class_node const &classType) {
            for (auto const &i : classType.field_types) {
                visitField(i);
            }
            for (auto const &i : classType.methods) {
                visitMethod(i);
            }
        }

        virtual void visitField(std::string const &type) {}

        virtual void visitMethod(method const &method) {
            visitReturn(method.returns);
            for (auto const &i : method.params) {
                visitParam(i);
            }
            for (auto const &i : method.locals) {
                visitLocal(i);
            }
            for (auto const &i : method.code) {
                visitInstruction(i);
            }
        }

        virtual void visitInstruction(il::instruction const &instruction) {}

        virtual void visitParam(std::string const &type) {}

        virtual void visitLocal(std::string const &type) {}

        virtual void visitReturn(std::string const &type) {}
    };


}


#endif //COMPBAU_CPP_RUNTIME_PARSER_VISITOR_H
