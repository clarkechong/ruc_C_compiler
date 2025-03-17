#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class DoWhile : public Node 
{
    public:
        DoWhile();
        DoWhile(NodePtr condition, NodePtr statement);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;


    private:
        NodePtr condition_;
        NodePtr statement_;
};

} // namespace ast