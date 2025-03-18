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
    // Process declarations first
    if (declaration_list_) {
        declaration_list_->EmitRISCV(stream, dst_reg, context);
    }
    
    // Process statements
    if (statement_list_) {
        statement_list_->EmitRISCV(stream, dst_reg, context);
    }
}

void Scope::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "{" << std::endl;
    
    indent_t inner_indent = indent;
    inner_indent++;
    
    if (declaration_list_) {
        declaration_list_->Print(stream, inner_indent);
    }
    
    if (statement_list_) {
        statement_list_->Print(stream, inner_indent);
    }
    
    stream << indent << "}" << std::endl;
}

} // namespace ast
