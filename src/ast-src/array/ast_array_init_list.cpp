#include "ast/array/ast_array_init_list.hpp"

namespace ast {

ArrayInitList::ArrayInitList(NodePtr first_element) 
    : NodeList(std::move(first_element))
{
}

void ArrayInitList::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if (context.scope_manager.InGlobalScope()) {
        NodeList::EmitRISCV(stream, dst_reg, context);
    } else {
        TypeSpecifier type = TypeSpecifier::INT; // default type
        
        
        int offset = 0;
        RecursiveEmit(stream, dst_reg, context, type, offset);
    }
}

void ArrayInitList::RecursiveEmit(std::ostream& stream, const std::string& base_ptr_reg,
                                Context& context, TypeSpecifier type, 
                                int& offset) const 
{
    int type_size = Context::GetSizeOfType(type);
    std::string store_instr = Context::GetStoreInstruction(type);
    
    const auto& children = GetChildren();
    
    for (size_t i = 0; i < children.size(); i++) {
        const auto& node = children[i];
        ArrayInitList* nested_list = dynamic_cast<ArrayInitList*>(node.get());
        
        if (nested_list != nullptr) {
            nested_list->RecursiveEmit(stream, base_ptr_reg, context, type, offset);
        } 
        else {
            std::string temp_reg = context.register_manager.AllocateRegister();
            
            node->EmitRISCV(stream, temp_reg, context);
            
            stream << "    " << store_instr << " " << temp_reg << ", "
                   << offset << "(" << base_ptr_reg << ")\n";
            
            offset += type_size;
            
            context.register_manager.DeallocateRegister(temp_reg);
        }
    }
}

void ArrayInitList::Print(std::ostream& stream, indent_t indent) const 
{
    stream << "{";
    
    NodeList::Print(stream, indent);
    
    stream << "}";
}

} // namespace ast
