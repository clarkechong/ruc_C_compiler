#include "ast/pointer/ast_pointer_declarator.hpp"

namespace ast {

PointerDeclarator::PointerDeclarator() 
{
}

void PointerDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void PointerDeclarator::Print(std::ostream& stream, int indent) const 
{
}

std::string PointerDeclarator::GetID() const 
{
    return ""; 
}

} // namespace ast