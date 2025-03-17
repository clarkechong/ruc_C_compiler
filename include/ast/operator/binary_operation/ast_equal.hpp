#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/operator/ast_binary_operator.hpp"

namespace ast {

class Equal : public BinaryOperator 
{
    public:
        Equal();
        Equal(NodePtr left, NodePtr right);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;
};

} // namespace ast
