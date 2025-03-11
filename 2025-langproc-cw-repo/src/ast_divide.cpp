#include "ast_context.hpp"
#include "ast_divide.hpp"
#include <sstream>

namespace ast {

void Divide::EmitRISC(std::ostream& stream, Context& context) const
{
    left_->EmitRISC(stream,context);
    stream << "add      a4,a5,0" <<std::endl;
    right_->EmitRISC(stream,context);
    stream << "div     a5,a4,a5" <<std::endl;
}

void Divide::Print(std::ostream& stream) const
{
    left_->Print(stream);
    stream << " + ";
    right_->Print(stream);
}



} // namespace ast
