#include "ast_context.hpp"
#include "ast_multiply.hpp"
#include <sstream>

namespace ast {

void Multiply::EmitRISC(std::ostream& stream, Context& context) const
{
    left_->EmitRISC(stream,context);
    stream << "add      a4,a5,0" <<std::endl;
    right_->EmitRISC(stream,context);
    stream << "mul     a5,a4,a5" <<std::endl;
}

void Multiply::Print(std::ostream& stream) const
{
    left_->Print(stream);
    stream << " * ";
    right_->Print(stream);
}



} // namespace ast
