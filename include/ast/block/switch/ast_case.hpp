#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class Case : public Node 
{
    public:
        Case();
        Case(NodePtr expression, NodePtr statement);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;

    private:
        NodePtr expression_;  // The case value to match
        NodePtr statement_;   // The statement to execute if matched
};

} // namespace ast