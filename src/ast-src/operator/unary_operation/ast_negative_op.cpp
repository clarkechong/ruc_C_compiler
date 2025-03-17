#include "ast/operator/unary_operation/ast_negative_op.hpp"

namespace ast {

NegativeOp::NegativeOp() 
{
}

void NegativeOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void NegativeOp::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
