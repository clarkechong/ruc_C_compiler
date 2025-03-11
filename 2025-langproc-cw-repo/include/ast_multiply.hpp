#pragma once

#include "ast_node.hpp"

namespace ast {

class Multiply  : public Node
{
private:
    NodePtr left_;
    NodePtr right_;

public:
    Multiply(NodePtr left, NodePtr right) : left_(std::move(left)),right_(std::move(right)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

} // namespace ast
