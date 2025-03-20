#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/operator/ast_unary_operator.hpp"

namespace ast {

class DereferenceOp : public UnaryOperator 
{
    public:
        DereferenceOp();
        DereferenceOp(NodePtr operand);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;
        const Node* GetOperand() const { return op_.get(); }

    private:
        ;
};

} // namespace ast
