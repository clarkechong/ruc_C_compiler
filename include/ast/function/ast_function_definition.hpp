#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/function/ast_function_declarator.hpp"

namespace ast {

class FunctionDefinition : public Node 
{
    public:
        FunctionDefinition();
        FunctionDefinition(NodePtr declaration_specifiers, NodePtr declarator, NodePtr compound_statement);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;


    private:
        NodePtr declaration_specifiers_;
        NodePtr declarator_;
        NodePtr compound_statement_;
};

} // namespace ast