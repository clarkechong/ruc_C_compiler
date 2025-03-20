#include "ast/ast_declaration.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/type/ast_declaration_type.hpp"
#include "ast/ast_init_declarator.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/array/ast_array_declarator.hpp"
#include "ast/pointer/ast_pointer_declarator.hpp"

namespace ast {

Declaration::Declaration(NodePtr type, NodePtr declarator)
: type_(std::move(type)), declarator_(std::move(declarator)) {}

void Declaration::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string decl_id;
    
    TypeSpecifier type_spec = TypeSpecifier::INT; // Default
    if (DeclarationType* type_node = dynamic_cast<DeclarationType*>(type_.get())) {
        type_spec = type_node->GetType();
    }

    // Handle InitDeclarator (variable with initialization)
    if (InitDeclarator* init_decl = dynamic_cast<InitDeclarator*>(declarator_.get())) {
        decl_id = init_decl->GetID();
        int stack_offset = context.stack_manager.AllocateStackAndLink(type_spec, decl_id, false, false);
        stream << "    # Allocated stack space for " << decl_id << " at offset " << stack_offset << std::endl;    

        std::string temp_reg = context.register_manager.AllocateRegister();
        init_decl->EmitRISCV(stream, temp_reg, context);
        context.stack_manager.StoreRegisterToVariable(stream, temp_reg, decl_id);

        context.register_manager.DeallocateRegister(temp_reg);
    }
    // Handle normal Identifier (simple variable)
    else if (Identifier* decl = dynamic_cast<Identifier*>(declarator_.get())) {
        decl_id = decl->GetID();
        int stack_offset = context.stack_manager.AllocateStackAndLink(type_spec, decl_id, false, false);
        stream << "    # Allocated stack space for " << decl_id << " at offset " << stack_offset << std::endl;
    }
    // Handle ArrayDeclarator (array variable)
    else if (ArrayDeclarator* array_decl = dynamic_cast<ArrayDeclarator*>(declarator_.get())) {
        decl_id = array_decl->GetID();
        std::vector<int> dimensions = array_decl->GetArrayIndexSpecifiers();
        
        int stack_offset = context.stack_manager.AllocateStackAndLink(type_spec, decl_id, false, true, dimensions);
        stream << "    # Allocated stack space for array " << decl_id << " at offset " << stack_offset << std::endl;
        
        stream << "    # Array dimensions:";
        for (int dim : dimensions) {
            stream << " " << dim;
        }
        stream << std::endl;
        
        // Get the array info from the symbol table and print debug information
        try {
            Variable_s array_var = context.scope_manager.GetVariable(decl_id);
            int total_size = Context::GetSizeOfType(type_spec);
            for (int dim : array_var.array_dimensions) {
                total_size *= dim;
            }
            
            stream << "    # Array debug info:" << std::endl;
            stream << "    #   - Name: " << decl_id << std::endl;
            stream << "    #   - Type: " << array_var.type << std::endl;
            stream << "    #   - Element size: " << Context::GetSizeOfType(array_var.type) << " bytes" << std::endl;
            stream << "    #   - Total size: " << total_size << " bytes" << std::endl;
            stream << "    #   - Stack offset: " << array_var.stack_offset << std::endl;
            stream << "    #   - Is array: " << (array_var.is_array ? "true" : "false") << std::endl;
            stream << "    #   - Dimensions: [";
            for (size_t i = 0; i < array_var.array_dimensions.size(); ++i) {
                stream << array_var.array_dimensions[i];
                if (i < array_var.array_dimensions.size() - 1) {
                    stream << ", ";
                }
            }
            stream << "]" << std::endl;
        } catch (const std::exception& e) {
            stream << "    # Error getting array debug info: " << e.what() << std::endl;
        }
    }
    // Handle PointerDeclarator (pointer variable)
    else if (PointerDeclarator* ptr_decl = dynamic_cast<PointerDeclarator*>(declarator_.get())) {
        decl_id = ptr_decl->GetID();
        int stack_offset = context.stack_manager.AllocateStackAndLink(type_spec, decl_id, true, false);
        stream << "    # Allocated stack space for pointer " << decl_id << " at offset " << stack_offset << std::endl;
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