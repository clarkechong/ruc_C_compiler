#include "ast_assignment.hpp"

namespace ast {

void Assignment::EmitRISC(std::ostream& stream, Context& context) const
{
    //identifier_->EmitRISC(stream,context);
    value_->EmitRISC(stream,context);
<<<<<<< HEAD
    stream << "sw    a5,-20(s0)"<<std::endl;
=======
    stream << "li    a5,";
    value_->Print(stream);
    stream << " " <<std::endl;
    stream << "sw   a5,-20(sp)"<<std::endl;

>>>>>>> temp-branch
}

void Assignment::Print(std::ostream& stream) const
{
    //context.AllocateVariable(declarator_,value_);
    identifier_-> Print(stream);
    stream << " = ";
    value_->Print(stream);
    stream << ";"<<std::endl;
}



} // namespace ast
