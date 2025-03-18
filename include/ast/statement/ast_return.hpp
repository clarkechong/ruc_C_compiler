#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class Return : public Node 
{
    public:
        Return();
        Return(NodePtr return_node);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;

    private:
        NodePtr return_node_; // The expression to return (can be nullptr for void return)
};

} // namespace ast