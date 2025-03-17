#include "ast/operator/binary_operation/ast_greater_than.hpp"

namespace ast {

GreaterThan::GreaterThan() 
    : BinaryOperator()
{
}

GreaterThan::GreaterThan(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void GreaterThan::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void GreaterThan::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
