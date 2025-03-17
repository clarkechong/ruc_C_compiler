#include "ast/operator/ast_binary_operator.hpp"

namespace ast {

BinaryOperator::BinaryOperator() 
{
}

void BinaryOperator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void BinaryOperator::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
