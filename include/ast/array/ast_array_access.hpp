#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class ArrayAccess : public Node 
{
    public:
        ArrayAccess();
        ArrayAccess(NodePtr array_id, NodePtr index);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;

    private:
        NodePtr array_id_;  // The array identifier
        NodePtr index_;     // The expression for the index
};

} // namespace ast