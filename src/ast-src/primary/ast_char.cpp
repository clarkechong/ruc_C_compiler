#include "ast/primary/ast_char.hpp"

namespace ast {

Char::Char(char value) : value_(value) {}

void Char::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Char::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
