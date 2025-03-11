#pragma once

#include "ast_node.hpp"

namespace ast {

class Unary  : public Node
{
private:
    NodePtr modulus_;

public:
    Unary(NodePtr modulus) : modulus_(std::move(modulus)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

} // namespace ast
