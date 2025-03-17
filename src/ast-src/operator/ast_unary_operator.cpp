#include "ast/operator/ast_unary_operator.hpp"

namespace ast {

UnaryOperator::UnaryOperator()
    : op_(nullptr)
{
}

UnaryOperator::UnaryOperator(NodePtr operand)
    : op_(std::move(operand))
{
}


void UnaryOperator::EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const
{
}

void UnaryOperator::Print(std::ostream &stream, int indent) const
{

}

} // namespace ast