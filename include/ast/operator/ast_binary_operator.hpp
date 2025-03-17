/*
    BASE CLASS FOR BINARY (2 OPERAND) OPERATORS
    - LEFT OPERAND
    - RIGHT OPERAND
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class BinaryOperator : public Node 
{
    public:
        BinaryOperator();
        BinaryOperator(NodePtr left_op, NodePtr right_op);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;

    protected:
        NodePtr left_op_;
        NodePtr right_op_;
};

} // namespace ast