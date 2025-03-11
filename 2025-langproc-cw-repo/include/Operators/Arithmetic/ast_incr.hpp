#pragma once

#include "ast_node.hpp"

namespace ast {

class Incr  : public Node
{
private:
    NodePtr modulus_;

public:
    Incr(NodePtr modulus) : modulus_(std::move(modulus)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

} // namespace ast
