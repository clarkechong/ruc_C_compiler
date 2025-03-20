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
    context.scope_manager.EnterNewScope();
    
    if (declaration_list_) {
        declaration_list_->EmitRISCV(stream, dst_reg, context);
    }
    
    if (statement_list_) {
        statement_list_->EmitRISCV(stream, dst_reg, context);
    }
    
    if (!statement_list_ || (statement_list_ && !dst_reg.empty() && dst_reg == "a0")) {
        stream << "    li a0, 0    # default return value for empty scope\n";
    }
    
    context.scope_manager.ExitScope();
}

void Scope::Print(std::ostream& stream, indent_t indent) const 
{
    stream << "{\n";
    
    if (declaration_list_) {
        declaration_list_->Print(stream, indent++);
    }
    
    if (statement_list_) {
        statement_list_->Print(stream, indent);
    }
    
    stream << "}\n";
}

} // namespace ast