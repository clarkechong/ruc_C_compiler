#pragma once

#include "ast_node.hpp"

namespace ast {

class Arrayassign : public Node
{
private:
    NodePtr identifier_;
    NodePtr index_;
    NodePtr value_;

public:
    Arrayassign(NodePtr identifier, NodePtr index, NodePtr value) : identifier_(std::move(identifier)),index_(std::move(index)),value_(std::move(value)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

} // namespace ast
