#include "ast/ast_declaration.hpp"

namespace ast {

Declaration::Declaration(NodePtr type, NodePtr declarator)
: type_(std::move(type)), declarator_(std::move(declarator)) {}

Declaration::Declaration(NodePtr type, NodePtr declarator, NodePtr value)
: type_(std::move(type)), declarator_(std::move(declarator)), value_(std::move(value)) {}

void Declaration::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Declaration::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast