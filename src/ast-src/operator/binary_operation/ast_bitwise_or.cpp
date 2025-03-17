#include "ast/operator/binary_operation/ast_bitwise_or.hpp"

namespace ast {

BitwiseOr::BitwiseOr() 
    : BinaryOperator()
{
}

BitwiseOr::BitwiseOr(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void BitwiseOr::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void BitwiseOr::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
