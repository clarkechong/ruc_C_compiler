#include "ast/operator/unary_operation/ast_sizeof.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/type/ast_declaration_type.hpp"
#include "ast/ast_nodelist.hpp"

namespace ast {

SizeOf::SizeOf() 
    : UnaryOperator() 
{
}

SizeOf::SizeOf(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void SizeOf::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (auto id = dynamic_cast<const Identifier*>(op_.get())) {
        std::string var_id = id->GetID();
        Variable_s var = context.scope_manager.GetVariable(var_id);
        int size = Context::GetSizeOfType(var.type);
        stream << "    li " << dst_reg << ", " << size << std::endl;
        
    } 
    else if (auto nodelist = dynamic_cast<const NodeList*>(op_.get())) {
        const std::vector<NodePtr>& children = nodelist->GetChildren();
        if (!children.empty() && children[0]) {
            if (auto type_node = dynamic_cast<DeclarationType*>(children[0].get())) {
                TypeSpecifier type = type_node->GetType();
                int size = Context::GetSizeOfType(type);
                stream << "    li " << dst_reg << ", " << size << std::endl;
                return;
            }
        }
        stream << "    li " << dst_reg << ", 0" << std::endl;
    }
    // THIS CASE NEVER ACTUALLY HAPPENS because type_specifier always goes through NodeList
    // else if (auto type_node = dynamic_cast<const DeclarationType*>(op_.get())) {
    //     TypeSpecifier type = type_node->GetType();
    //     int size = Context::GetSizeOfType(type);
    //     stream << "    li " << dst_reg << ", " << size << std::endl;
    // }
    // else {
    //     stream << "    li " << dst_reg << ", 0" << std::endl;
    // }
}

void SizeOf::Print(std::ostream& stream, indent_t indent) const 
{
    stream << "sizeof(";
    if (op_) {
        op_->Print(stream, indent);
    }
    stream << ")";
}

} // namespace ast