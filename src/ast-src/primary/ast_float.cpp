#include "ast/primary/ast_float.hpp"

namespace ast {

Float::Float(double value) : value_(value) {
}

void Float::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Float::Print(std::ostream& stream, indent_t indent) const 
{
    stream << value_;
}

} // namespace ast
