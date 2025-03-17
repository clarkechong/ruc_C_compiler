#include "ast/primary/ast_float.hpp"

namespace ast {

Float::Float(double value) : value_(value) {
    std::cout << "new float for yo mama: " << value_ << "\n";
}

void Float::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Float::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
