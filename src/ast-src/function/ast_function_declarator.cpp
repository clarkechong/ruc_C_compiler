#include "ast/function/ast_function_declarator.hpp"

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
}

void FunctionDeclarator::Print(std::ostream& stream, indent_t indent) const 
{
    direct_declarator_->Print(stream, 0);
    stream << "(";
    if (parameter_list_)
    {
        parameter_list_->Print(stream, 0);
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