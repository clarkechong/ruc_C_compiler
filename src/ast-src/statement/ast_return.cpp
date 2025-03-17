#include "ast/statement/ast_return.hpp"

namespace ast {

Return::Return() 
{
}

void Return::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Return::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast