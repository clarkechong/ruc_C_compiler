#include "ast/operator/binary_operation/ast_right_shift.hpp"

namespace ast {

RightShift::RightShift() 
    : BinaryOperator()
{
}

RightShift::RightShift(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void RightShift::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void RightShift::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
