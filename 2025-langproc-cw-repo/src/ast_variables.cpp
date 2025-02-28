#include "ast_variable.hpp"

namespace ast {

void Variable::EmitRISC(std::ostream& stream, Context& context) const
{
    (void)context;
    stream << "nop" << std::endl;
}

void Variable::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " " ;

    declarator_->Print(stream);
    stream << ";" <<std::endl;
}



} // namespace ast
