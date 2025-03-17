#include "ast/primary/ast_string.hpp"

namespace ast {

String::String(std::string value) : value_(value) {
}

void String::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void String::Print(std::ostream& stream, indent_t indent) const 
{
    stream << "\"" << value_ << "\"";
}

} // namespace ast
