#include "ast/operator/binary_operation/ast_less_than.hpp"

namespace ast {

LessThan::LessThan() 
    : BinaryOperator()
{
}

LessThan::LessThan(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LessThan::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void LessThan::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
