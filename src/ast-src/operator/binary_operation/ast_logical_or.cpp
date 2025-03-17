#include "ast/operator/binary_operation/ast_logical_or.hpp"

namespace ast {

LogicalOr::LogicalOr() 
    : BinaryOperator()
{
}

LogicalOr::LogicalOr(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LogicalOr::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void LogicalOr::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
