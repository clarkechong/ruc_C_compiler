#include "ast_externdef.hpp"

namespace ast {

void Externdef::EmitRISC(std::ostream& stream, Context& context) const
{
    (void)context;
    stream << " ";
}

void Externdef::Print(std::ostream& stream) const
{
    stream << type_ <<  identifier_ << "();" << std::endl;
}


} // namespace ast
