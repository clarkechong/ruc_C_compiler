#include "ast/primary/ast_integer.hpp"

namespace ast {

Integer::Integer(int value) : value_(value) {
    std::cout << "new integer for yo mama: " << value_ << "\n";
}

void Integer::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Integer::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
