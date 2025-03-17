#include "ast/type/struct/ast_struct_member.hpp"

namespace ast {

StructMember::StructMember() 
{
}

void StructMember::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void StructMember::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
