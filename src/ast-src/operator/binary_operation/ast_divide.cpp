#include "ast/operator/binary_operation/ast_divide.hpp"

namespace ast {

Divide::Divide() 
    : BinaryOperator()
{
}

Divide::Divide(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Divide::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Divide::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
