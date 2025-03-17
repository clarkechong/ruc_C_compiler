#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class Scope : public Node 
{
    public:
        Scope();
        Scope(NodePtr declaration_list, NodePtr statement_list);
                
        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;

    private:
        NodePtr declaration_list_;
        NodePtr statement_list_;
};

} // namespace ast
