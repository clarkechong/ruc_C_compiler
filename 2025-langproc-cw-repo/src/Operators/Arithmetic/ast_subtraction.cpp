#include "ast_context.hpp"
#include "Operators/Arithmetic/ast_subtraction.hpp"
#include <sstream>

namespace ast {

void Subtraction::EmitRISC(std::ostream& stream, Context& context) const
{
    left_->EmitRISC(stream,context);
    stream << "add      a4,a5,0" <<std::endl;
    right_->EmitRISC(stream,context);
    stream << "sub     a5,a4,a5" <<std::endl;
}

void Subtraction::Print(std::ostream& stream) const
{
    left_->Print(stream);
    stream << " - ";
    right_->Print(stream);
}



} // namespace ast
