#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/operator/ast_unary_operator.hpp"

namespace ast {

class SizeOf : public UnaryOperator 
{
    public:
        SizeOf();
        SizeOf(NodePtr operand);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;
};

} // namespace ast
