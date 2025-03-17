#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/operator/ast_binary_operator.hpp"

namespace ast {

class Sub : public BinaryOperator 
{
    public:
        Sub();
        Sub(NodePtr left, NodePtr right);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;
};

} // namespace ast