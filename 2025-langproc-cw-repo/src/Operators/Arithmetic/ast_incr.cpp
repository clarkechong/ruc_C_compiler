#include "ast_context.hpp"
#include "Operators/Arithmetic/ast_incr.hpp"
#include <sstream>

namespace ast {

void Incr::EmitRISC(std::ostream& stream, Context& context) const
{
    modulus_->EmitRISC(stream,context);
    stream << "add a5,a5,1" << std::endl;
}

void Incr::Print(std::ostream& stream) const
{
    modulus_->Print(stream);
    stream << "++";
}



} // namespace ast
