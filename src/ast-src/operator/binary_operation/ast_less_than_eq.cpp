#include "ast/operator/binary_operation/ast_less_than_eq.hpp"

namespace ast {

LessThanEq::LessThanEq() 
    : BinaryOperator()
{
}

LessThanEq::LessThanEq(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LessThanEq::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void LessThanEq::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
