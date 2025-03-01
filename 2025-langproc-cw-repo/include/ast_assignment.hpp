#pragma once

#include "ast_node.hpp"

namespace ast {

class Assignment : public Node
{
private:
    NodePtr identifier_;
    NodePtr value_;

public:
    Assignment(NodePtr identifier, NodePtr value) : identifier_(std::move(identifier)),value_(std::move(value)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
