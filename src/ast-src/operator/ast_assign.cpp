#include "ast/operator/ast_assign.hpp"

namespace ast {

Assign::Assign() 
{
}

void Assign::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Assign::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
