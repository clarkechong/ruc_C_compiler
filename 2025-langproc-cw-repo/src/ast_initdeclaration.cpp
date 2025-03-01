#include "ast_initdeclaration.hpp"

namespace ast {

void InitDecl::EmitRISC(std::ostream& stream, Context& context) const
{
    declarator_->EmitRISC(stream,context);
    stream << "sw    a5,-20(s0)"<<std::endl;
}

void InitDecl::Print(std::ostream& stream) const
{
    //context.AllocateVariable(declarator_,value_);
    stream << declaration_specifiers_ << " ";
    declarator_-> Print(stream) ;
    stream << ";"<<std::endl;
}



} // namespace ast
