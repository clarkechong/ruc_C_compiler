#include "ast_context.hpp"
#include "Operators/Arithmetic/ast_decr.hpp"
#include <sstream>

namespace ast {

void Decr::EmitRISC(std::ostream& stream, Context& context) const
{
    modulus_->EmitRISC(stream,context);
    stream << "sub a5,a5,1" << std::endl;
}

void Decr::Print(std::ostream& stream) const
{
    stream << " +";
    modulus_->Print(stream);
}



} // namespace ast
