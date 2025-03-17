#include "ast_funcprim.hpp"

namespace ast {

void Funcprim::EmitRISC(std::ostream& stream, Context& context) const
{
    if(parameter_list_ != nullptr){
        parameter_list_->EmitRISC(stream,context);
    }
    stream << "call    ";
    declarator_->Print(stream);
    stream <<std::endl;
    stream << "mv      a5,a0"<<std::endl;
}

void Funcprim::Print(std::ostream& stream) const
{
    declarator_->Print(stream);
    stream << "(";
    if(parameter_list_ != nullptr){
        parameter_list_->Print(stream);
    }
    else{
        stream << "(";
    }
    stream << ")" ;
}


} // namespace ast
