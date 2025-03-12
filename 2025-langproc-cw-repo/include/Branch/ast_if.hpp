#pragma once

#include "ast_node.hpp"

namespace ast {

class EILF : public Node
{
private:
    NodePtr condexpression_;
    NodePtr ifstatement_;
    NodePtr elsestatement_;

public:
    EILF(NodePtr condexpression, NodePtr ifstatement, NodePtr elsestatement) : condexpression_(std::move(condexpression)), ifstatement_(std::move(ifstatement)),elsestatement_(std::move(elsestatement)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
