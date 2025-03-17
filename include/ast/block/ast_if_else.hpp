#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class IfElse : public Node 
{
    public:
        IfElse();
        IfElse(NodePtr condition, NodePtr if_statement, NodePtr else_statement);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;


    private:
        NodePtr condition_;
        NodePtr if_statement_;
        NodePtr else_statement_;
};

} // namespace ast