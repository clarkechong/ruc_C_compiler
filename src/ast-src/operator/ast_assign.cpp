#include "ast/operator/ast_assign.hpp"

namespace ast {

Assign::Assign() 
    : BinaryOperator()
{
}

Assign::Assign(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Assign::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Assign::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
