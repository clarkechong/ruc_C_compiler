#include "ast/block/ast_if_else.hpp"

namespace ast {

IfElse::IfElse(NodePtr condition, NodePtr if_statement, NodePtr else_statement)
: condition_(std::move(condition)), if_statement_(std::move(if_statement)), else_statement_(std::move(else_statement)) {}

void IfElse::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void IfElse::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
