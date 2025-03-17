#include "ast/operator/unary_operation/ast_sizeof.hpp"

namespace ast {

SizeOf::SizeOf() 
{
}

void SizeOf::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void SizeOf::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
