/*
    BASE CLASS FOR UNARY OPERATORS
    - OPERAND
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class UnaryOperator : public Node 
{
    public:
        UnaryOperator();

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;


    private:
        NodePtr op_;
};

} // namespace ast