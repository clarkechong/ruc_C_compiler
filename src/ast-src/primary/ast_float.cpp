#include "ast/primary/ast_float.hpp"

namespace ast {

Float::Float(float value) : value_(value) {}

void Float::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Float::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
