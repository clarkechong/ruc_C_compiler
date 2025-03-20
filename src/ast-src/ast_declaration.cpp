#include "ast/ast_declaration.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/type/ast_declaration_type.hpp"
#include "ast/ast_init_declarator.hpp"
#include "ast/ast_declarator.hpp"

namespace ast {

Declaration::Declaration(NodePtr type, NodePtr declarator)
: type_(std::move(type)), declarator_(std::move(declarator)) {}

void Declaration::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (!type_ || !declarator_) {
        return;
    }

    std::string decl_id;
    
    TypeSpecifier type_spec = TypeSpecifier::INT; // Default
    DeclarationType* type_node = dynamic_cast<DeclarationType*>(type_.get());
    if (type_node) {
        type_spec = type_node->GetType();
    }

    if(InitDeclarator* init_decl = dynamic_cast<InitDeclarator*>(declarator_.get())) {
        decl_id = init_decl->GetID();
        int stack_offset = context.stack_manager.AllocateStackAndLink(type_spec, decl_id, false, false);
        stream << "    # Allocated stack space for " << decl_id << " at offset " << stack_offset << std::endl;    

        std::string temp_reg = context.register_manager.AllocateRegister();
        init_decl->EmitRISCV(stream, temp_reg, context);
        context.stack_manager.StoreRegisterToVariable(stream, temp_reg, decl_id);

        context.register_manager.DeallocateRegister(temp_reg);

    }

    else if(Declarator* decl = dynamic_cast<Declarator*>(declarator_.get())) {
        decl_id = decl->GetID();
        int stack_offset = context.stack_manager.AllocateStackAndLink(type_spec, decl_id, false, false);
        stream << "    # Allocated stack space for " << decl_id << " at offset " << stack_offset << std::endl;    
    }
    

        

}

void Declaration::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "Declaration [" << std::endl;
    
    stream << indent << "Type:" << std::endl;
    if (type_) {
        type_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "Declarator:" << std::endl;
    if (declarator_) {
        declarator_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "]" << std::endl;
}

} // namespace ast