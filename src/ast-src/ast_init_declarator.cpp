#include "ast/ast_init_declarator.hpp"

namespace ast {

InitDeclarator::InitDeclarator() 
    : declarator_(nullptr), initializer_(nullptr)
{
}

InitDeclarator::InitDeclarator(NodePtr declarator, NodePtr initializer)
    : declarator_(std::move(declarator)), initializer_(std::move(initializer))
{
}

void InitDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (!declarator_) {
        return;
    }
    
    Declarator* decl = dynamic_cast<Declarator*>(declarator_.get());
    if (!decl) {
        throw std::runtime_error("Invalid declarator in initialization");
    }
    
    std::string id = decl->GetID();
    
    declarator_->EmitRISCV(stream, dst_reg, context);
    
    if (initializer_) {
        initializer_->EmitRISCV(stream, dst_reg, context);
        
        // std::string temp_reg = context.register_manager.AllocateRegister();
        // TypeSpecifier type = TypeSpecifier::INT;
        // if (context.scope_manager.VariableExists(id)) {
        //     type = context.scope_manager.GetVariable(id).type;
        // }
        
        // int stack_offset = context.scope_manager.GetVariable(id).stack_offset;
        // std::string store_instr = Context::GetStoreInstruction(type);
        
        // stream << "    " << store_instr << " " << temp_reg << ", " << stack_offset << "(s0)\n";
        
        // context.register_manager.DeallocateRegister(temp_reg);
    }
}

void InitDeclarator::Print(std::ostream& stream, indent_t indent) const 
{
    if (declarator_) {
        declarator_->Print(stream, indent);
    }
    
    if (initializer_) {
        stream << " = ";
        initializer_->Print(stream, indent);
    }
}

std::string InitDeclarator::GetID() const 
{
    if (declarator_) {
        Declarator* decl = dynamic_cast<Declarator*>(declarator_.get());
        if (decl) {
            return decl->GetID();
        }
    }
    return "";
}

} // namespace ast