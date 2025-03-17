#include "ast/operator/unary_operation/ast_negative_op.hpp"

namespace ast {

NegativeOp::NegativeOp() 
{
}

NegativeOp::NegativeOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void NegativeOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void NegativeOp::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
