#include "ast/primary/ast_identifier.hpp"
#include "ast/type/ast_declaration_type.hpp"

namespace ast {

Identifier::Identifier(std::string id) : id_(id) {
}

void Identifier::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (context.scope_manager.VariableExists(id_)) {
        context.stack_manager.LoadVariableToRegister(stream, dst_reg, id_);
    } else {
        // TypeSpecifier type = TypeSpecifier::INT; // NEEDS TO KNOW THIS FROM PARENT
        
    }
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
