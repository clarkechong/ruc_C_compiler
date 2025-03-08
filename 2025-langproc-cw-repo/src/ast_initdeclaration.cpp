#include "ast_initdeclaration.hpp"
#include "ast_constant.hpp"

namespace ast {

void InitDecl::EmitRISC(std::ostream& stream, Context& context) const
{

    if( value_ != NULL){
        value_->EmitRISC(stream,context);
        stream << "sw   a5,-20(s0)" << std::endl;
    }

}

void InitDecl::Print(std::ostream& stream) const
{
    //context.AllocateVariable(declarator_,value_);
    stream << declaration_specifiers_ << " ";
    declarator_-> Print(stream);
    if ( value_ != NULL){
        stream << "=" ;
        value_-> Print(stream);
    }
    stream << ";"<<std::endl;
}



} // namespace ast
