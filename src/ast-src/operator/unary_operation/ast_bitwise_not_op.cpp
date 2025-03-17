#include "ast/operator/unary_operation/ast_bitwise_not_op.hpp"

namespace ast {

BitwiseNotOp::BitwiseNotOp() 
{
}

BitwiseNotOp::BitwiseNotOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void BitwiseNotOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void BitwiseNotOp::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
