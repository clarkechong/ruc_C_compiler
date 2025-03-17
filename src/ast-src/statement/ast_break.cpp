#include "ast/statement/ast_break.hpp"

namespace ast {

Break::Break() 
{
}

void Break::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Break::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "break;" << std::endl;
}

} // namespace ast