#include "ast_retvar.hpp"
#include <sstream>


namespace ast {

void RetVar::EmitRISC(std::ostream& stream, Context& context) const
{
    std::ostringstream interm;
    declarator_->Print(interm);
    std::string name = interm.str();
    int offset = context.GetVariableOffset(name);
    stream <<"lw      a5,"<< offset <<"(s0)"<<std::endl;
    stream <<"mv      a0,a5"<< std::endl;
    stream <<"lw      s0,28(sp)"<< std::endl;
    stream <<"addi    sp,sp,32"<< std::endl;
    stream <<"jr      ra"<< std::endl;
}

void RetVar::Print(std::ostream& stream) const
{
    stream << "return";
    if (declarator_ != nullptr)
    {
        stream << " ";
        declarator_->Print(stream);
    }
    stream << ";" << std::endl;
}


}
