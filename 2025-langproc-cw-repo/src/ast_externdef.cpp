#include "ast_externdef.hpp"

namespace ast {

void Externdef::EmitRISC(std::ostream& stream, Context& context) const
{
    (void)context;
    stream << " ";
}

void Externdef::Print(std::ostream& stream) const
{
    stream << type_ << " ";
    identifier_->Print(stream);
    if(parameter_list_ != nullptr){
        parameter_list_->Print(stream);
        stream << ";" <<std::endl;
    }
    else{
        stream << " ();" << std::endl;
    }
}


} // namespace ast
