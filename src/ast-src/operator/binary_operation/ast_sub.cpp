#include "ast/operator/binary_operation/ast_sub.hpp"

namespace ast {

Sub::Sub() 
    : BinaryOperator()
{
}

Sub::Sub(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Sub::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Sub::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
