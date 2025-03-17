#include "ast/operator/binary_operation/ast_bitwise_and.hpp"

namespace ast {

BitwiseAnd::BitwiseAnd() 
    : BinaryOperator()
{
}

BitwiseAnd::BitwiseAnd(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void BitwiseAnd::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void BitwiseAnd::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
