#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class For : public Node 
{
    public:
        For(NodePtr initializer, NodePtr condition, NodePtr increment, NodePtr statement)
        : initializer_(std::move(initializer)), condition_(std::move(condition)), increment_(std::move(increment)), statement_(std::move(statement)) {};

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;


    private:
        NodePtr initializer_;
        NodePtr condition_;
        NodePtr increment_;
        NodePtr statement_; // i.e. the {} body of the for loop
};

} // namespace ast