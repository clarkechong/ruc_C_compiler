#include "ast/statement/ast_continue.hpp"

namespace ast {

Continue::Continue() 
{
}

void Continue::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Continue::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "continue;" << std::endl;
}

} // namespace ast