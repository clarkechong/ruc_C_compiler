#include "ast_initdeclaration.hpp"

namespace ast {

void InitDecl::EmitRISC(std::ostream& stream, Context& context) const
{
    (void)context;
    stream << "nop" << std::endl;
}

void InitDecl::Print(std::ostream& stream) const
{
    //context.AllocateVariable(declarator_,value_);
    stream << declaration_specifiers_ << " ";
    declarator_-> Print(stream) ;
    stream << ";"<<std::endl;
}



} // namespace ast
