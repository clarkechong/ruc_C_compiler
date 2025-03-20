#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/type/ast_declaration_type.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class FunctionParameter : public Node 
{
    public:
        FunctionParameter(NodePtr type, NodePtr declarator);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;


    private:
        NodePtr type_;
        NodePtr declarator_; // probably just class Identifier
};

} // namespace ast