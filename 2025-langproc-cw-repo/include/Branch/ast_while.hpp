#pragma once

#include "ast_node.hpp"

namespace ast {

class Whilefunc : public Node
{
private:
    NodePtr condexpression_;
    NodePtr statement_;

public:
    Whilefunc(NodePtr condexpression, NodePtr statement) : condexpression_(std::move(condexpression)), statement_(std::move(statement)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
