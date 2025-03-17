#include "ast/operator/binary_operation/ast_multiply.hpp"

namespace ast {

Multiply::Multiply() 
    : BinaryOperator()
{
}

Multiply::Multiply(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Multiply::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Multiply::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
