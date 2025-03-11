#include "ast_context.hpp"
#include "Operators/Arithmetic/ast_unary.hpp"
#include <sstream>

namespace ast {

void Unary::EmitRISC(std::ostream& stream, Context& context) const
{
    modulus_->EmitRISC(stream,context);
    stream << "neg a5,a5" << std::endl;
}

void Unary::Print(std::ostream& stream) const
{
    stream << " -";
    modulus_->Print(stream);
}



} // namespace ast
