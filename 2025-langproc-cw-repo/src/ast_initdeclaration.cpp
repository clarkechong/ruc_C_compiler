#include "ast_initdeclaration.hpp"

namespace ast {

void InitDecl::EmitRISC(std::ostream& stream, Context& context) const
{
    (void)context;
    stream << "nop" << std::endl;
}

void InitDecl::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " " << declarator_ << " ;"<<std::endl;
}



} // namespace ast
