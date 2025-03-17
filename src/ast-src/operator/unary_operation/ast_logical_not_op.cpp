#include "ast/operator/unary_operation/ast_logical_not_op.hpp"

namespace ast {

LogicalNotOp::LogicalNotOp() 
{
}

void LogicalNotOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void LogicalNotOp::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
