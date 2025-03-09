#include "ast_variable.hpp"
#include "ast_context.hpp"

namespace ast {

void Variable::EmitRISC(std::ostream& stream, Context& context) const
{
    context.AllocateVariable(identifier_);
    stream << "nop" << std::endl;
}

void Variable::Print(std::ostream& stream) const
{
    stream << type_ << " " << identifier_ << ";" << std::endl;
}

std::string Variable::getid() const
{
    return identifier_;
}


} // namespace ast
