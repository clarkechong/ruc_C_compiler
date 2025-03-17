#include "ast/primary/ast_integer.hpp"

namespace ast {

Integer::Integer(int value) : value_(value) {
}

void Integer::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Integer::Print(std::ostream& stream, indent_t indent) const 
{
    stream << value_;
}

} // namespace ast
