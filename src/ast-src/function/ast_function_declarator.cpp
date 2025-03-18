#include "ast/function/ast_function_declarator.hpp"
#include "ast/ast_declarator.hpp"

namespace ast {

FunctionDeclarator::FunctionDeclarator() 
    : direct_declarator_(nullptr), parameter_list_(nullptr)
{
}

FunctionDeclarator::FunctionDeclarator(NodePtr direct_declarator, NodePtr parameter_list)
    : direct_declarator_(std::move(direct_declarator)), parameter_list_(std::move(parameter_list))
{
}

void FunctionDeclarator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string func_name = GetID();
    
    TypeSpecifier return_type = TypeSpecifier::INT;
    
    std::vector<TypeSpecifier> param_types;
    if (parameter_list_) {
        param_types.push_back(TypeSpecifier::INT); // in future implement parameter_declaration node type, which can extract typespecifier from parameters
    }
    
    context.scope_manager.AddFunction(func_name, return_type, param_types);
    
    stream << func_name << ":\n";
    
    context.stack_manager.InitiateFrame(stream);
    
    if (parameter_list_) {
        parameter_list_->EmitRISCV(stream, dst_reg, context);
    }
}

void FunctionDeclarator::Print(std::ostream& stream, indent_t indent) const 
{
    if (direct_declarator_) {
        direct_declarator_->Print(stream, indent);
    }
    
    stream << "(";
    
    if (parameter_list_) {
        parameter_list_->Print(stream, indent);
    }
    
    stream << ")";
}

std::string FunctionDeclarator::GetID() const 
{
    if (direct_declarator_) {
        Declarator* declarator = dynamic_cast<Declarator*>(direct_declarator_.get());
        if (declarator) {
            return declarator->GetID();
        }
    }
    return ""; 
}

} // namespace ast