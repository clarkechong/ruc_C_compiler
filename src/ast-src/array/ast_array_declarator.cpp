#include "ast/array/ast_array_declarator.hpp"

namespace ast {

ArrayDeclarator::ArrayDeclarator() {
}

void ArrayDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const {
}

void ArrayDeclarator::Print(std::ostream& stream, int indent) const {
}

std::string ArrayDeclarator::GetID() const {
    return ""; 
}

} // namespace ast