#include "ast/primary/ast_identifier.hpp"

namespace ast {

Identifier::Identifier(std::string id) : id_(id) {
    std::cout << "new identifier for yo mama: " << id_ << "\n";
}

void Identifier::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Identifier::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
