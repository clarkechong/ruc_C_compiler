#include "ast_jump_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, Context& context) const
{
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, context);
    }
    stream <<"mv      a0,a5"<< std::endl;
    stream <<"lw      s0,28(sp)"<< std::endl;
    stream <<"addi    sp,sp,32"<< std::endl;
    stream <<"jr      ra"<< std::endl;
}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}


}
