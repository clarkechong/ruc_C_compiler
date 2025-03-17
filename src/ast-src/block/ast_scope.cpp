#include "ast/block/ast_scope.hpp"

namespace ast {

Scope::Scope()
: declaration_list_(nullptr), statement_list_(nullptr)
{
}

Scope::Scope(NodePtr declaration_list, NodePtr statement_list)
: declaration_list_(std::move(declaration_list)), statement_list_(std::move(statement_list))
{
}

void Scope::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Scope::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
