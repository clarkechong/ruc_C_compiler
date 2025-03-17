#include "ast/primary/ast_string.hpp"

namespace ast {

String::String(std::string value) : value_(value) {
    // std::cout << "new string for yo mama: " << value_ << "\n";
}

void String::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void String::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
