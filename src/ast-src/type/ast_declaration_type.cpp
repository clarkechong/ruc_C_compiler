#include "ast/type/ast_declaration_type.hpp"

namespace ast {

DeclarationType::DeclarationType(TypeSpecifier type) : type_(type) {
}

void DeclarationType::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void DeclarationType::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << type_;
}

} // namespace ast
