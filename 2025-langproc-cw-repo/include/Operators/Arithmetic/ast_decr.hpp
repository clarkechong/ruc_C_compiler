#pragma once

#include "ast_node.hpp"

namespace ast {

class Decr  : public Node
{
private:
    NodePtr modulus_;

public:
    Decr(NodePtr modulus) : modulus_(std::move(modulus)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

} // namespace ast
