#include "ast/operator/binary_operation/ast_modulus.hpp"

namespace ast {

Modulus::Modulus() 
    : BinaryOperator()
{
}

Modulus::Modulus(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Modulus::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Modulus::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
