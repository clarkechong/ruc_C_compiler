#pragma once

#include "ast_node.hpp"

namespace ast {

class RetVar : public Node
{
private:
    NodePtr declarator_;

public:
    RetVar(NodePtr declarator) : declarator_(std::move(declarator)) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
