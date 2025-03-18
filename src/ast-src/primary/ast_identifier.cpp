#include "ast/primary/ast_identifier.hpp"

namespace ast {

Identifier::Identifier(std::string id) : id_(id) {
    // std::cout << id_;
}

void Identifier::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Identifier::Print(std::ostream& stream, indent_t indent) const 
{
    stream << id_;
}

std::string Identifier::GetID() const
{
    return id_;
}

} // namespace ast
