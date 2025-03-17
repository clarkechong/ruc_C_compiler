#include "ast/operator/unary_operation/ast_post_dec.hpp"

namespace ast {

PostDec::PostDec()
    : UnaryOperator()
{
}

PostDec::PostDec(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void PostDec::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void PostDec::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
