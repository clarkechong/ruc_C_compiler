#include "ast/operator/binary_operation/ast_left_shift.hpp"

namespace ast {

LeftShift::LeftShift() 
    : BinaryOperator()
{
}

LeftShift::LeftShift(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LeftShift::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void LeftShift::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
