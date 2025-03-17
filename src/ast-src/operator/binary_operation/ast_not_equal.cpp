#include "ast/operator/binary_operation/ast_not_equal.hpp"

namespace ast {

NotEqual::NotEqual() 
    : BinaryOperator()
{
}

NotEqual::NotEqual(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void NotEqual::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void NotEqual::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
