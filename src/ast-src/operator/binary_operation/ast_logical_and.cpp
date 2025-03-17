#include "ast/operator/binary_operation/ast_logical_and.hpp"

namespace ast {

LogicalAnd::LogicalAnd() 
    : BinaryOperator()
{
}

LogicalAnd::LogicalAnd(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LogicalAnd::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void LogicalAnd::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
