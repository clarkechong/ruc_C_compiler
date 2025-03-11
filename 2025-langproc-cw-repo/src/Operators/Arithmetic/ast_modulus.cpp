#include "ast_context.hpp"
#include "Operators/Arithmetic/ast_modulus.hpp"
#include <sstream>

namespace ast {

void Modulus::EmitRISC(std::ostream& stream, Context& context) const
{
    left_->EmitRISC(stream,context);
    stream << "add      a4,a5,0" <<std::endl;
    right_->EmitRISC(stream,context);
    stream << "rem     a5,a4,a5" <<std::endl;
}

void Modulus::Print(std::ostream& stream) const
{
    left_->Print(stream);
    stream << " % ";
    right_->Print(stream);
}



} // namespace ast
