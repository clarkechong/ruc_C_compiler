#include "ast/function/ast_function_parameter.hpp"
#include "ast/type/ast_declaration_type.hpp"
#include "ast/ast_declarator.hpp"

namespace ast {

FunctionParameter::FunctionParameter(NodePtr type, NodePtr declarator)
    : type_(std::move(type)), declarator_(std::move(declarator))
{
}

void FunctionParameter::EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const
{
    bool is_float = false;
    TypeSpecifier param_type = TypeSpecifier::INT; // Default to INT if type not specified
    
    if (type_) {
        const DeclarationType* decl_type = dynamic_cast<const DeclarationType*>(type_.get());
        if (decl_type) {
            param_type = decl_type->GetType();
            is_float = (param_type == TypeSpecifier::FLOAT || param_type == TypeSpecifier::DOUBLE);
        }
    }
    
    std::string arg_reg = context.register_manager.AllocateArgumentRegister(is_float);
    
    std::string param_id;
    if (declarator_) {
        const Declarator* declarator = dynamic_cast<const Declarator*>(declarator_.get());
        if (declarator) {
            param_id = declarator->GetID();
        } else {
            stream << "    # Error: Could not cast declarator to Declarator*" << std::endl;
            return;
        }
                
        int stack_offset = context.stack_manager.AllocateStackAndLink(
            param_type, 
            param_id, 
            false,  // is_ptr - should be determined from declarator maybe add new virtual function to declarator to retreive this info
            false   // is_array - should be determined from declarator
        );
        
        context.stack_manager.StoreRegisterToVariable(stream, arg_reg, param_id);
    }
}

void FunctionParameter::Print(std::ostream &stream, indent_t indent) const
{
}

} // namespace ast