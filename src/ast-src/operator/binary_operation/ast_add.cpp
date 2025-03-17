#include "ast/operator/binary_operation/ast_add.hpp"

namespace ast {

Add::Add() 
    : BinaryOperator()
{
}

Add::Add(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Add::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Add::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
