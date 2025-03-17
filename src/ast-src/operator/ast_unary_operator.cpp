#include "ast/operator/ast_unary_operator.hpp"

namespace ast {

UnaryOperator::UnaryOperator()
{
}

void UnaryOperator::EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const
{
}

void UnaryOperator::Print(std::ostream &stream, int indent) const
{
}

} // namespace ast