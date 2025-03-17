#include "ast/function/ast_function_declarator.hpp"

namespace ast {

FunctionDeclarator::FunctionDeclarator() 
{
}

void FunctionDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void FunctionDeclarator::Print(std::ostream& stream, int indent) const 
{
}

std::string FunctionDeclarator::GetID() const 
{
    return ""; 
}

} // namespace ast