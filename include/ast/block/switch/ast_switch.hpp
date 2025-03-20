#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class Switch : public Node 
{
    public:
        Switch();
        Switch(NodePtr expression, NodePtr statement);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;

    private:
        NodePtr expression_;  // The expression to switch on
        NodePtr statement_;   // The compound statement containing case statements
};

} // namespace ast