#include "ast/pointer/ast_pointer_declarator.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

PointerDeclarator::PointerDeclarator() 
    : pointer_(nullptr), direct_declarator_(nullptr)
{
}

PointerDeclarator::PointerDeclarator(NodePtr pointer, NodePtr direct_declarator)
    : pointer_(std::move(pointer)), direct_declarator_(std::move(direct_declarator))
{
}

void PointerDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (direct_declarator_) {
        direct_declarator_->EmitRISCV(stream, dst_reg, context);
    }
}

void PointerDeclarator::Print(std::ostream& stream, indent_t indent) const 
{
}

std::string PointerDeclarator::GetID() const 
{
    if (direct_declarator_) {
        if (Declarator* decl = dynamic_cast<Declarator*>(direct_declarator_.get())) {
            return decl->GetID();
        }
    }
    
    return ""; 
}

} // namespace ast