#include "ast/pointer/ast_pointer_declarator.hpp"

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
}

void PointerDeclarator::Print(std::ostream& stream, indent_t indent) const 
{
}

std::string PointerDeclarator::GetID() const 
{
    return ""; 
}

} // namespace ast