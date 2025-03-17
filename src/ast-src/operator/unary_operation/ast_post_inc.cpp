#include "ast/operator/unary_operation/ast_post_inc.hpp"

namespace ast {

PostInc::PostInc()
    : UnaryOperator()
{
}

PostInc::PostInc(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void PostInc::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void PostInc::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
