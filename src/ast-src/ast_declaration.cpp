#include "ast/ast_declaration.hpp"

namespace ast {

Declaration::Declaration(NodePtr type, NodePtr declarator)
: type_(std::move(type)), declarator_(std::move(declarator)) {}

Declaration::Declaration(NodePtr type, NodePtr declarator, NodePtr value)
: type_(std::move(type)), declarator_(std::move(declarator)), value_(std::move(value)) {}

void Declaration::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Declaration::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent;
    
    if (type_) {
        type_->Print(stream, indent_t(0));
        stream << " ";
    }
    
    if (declarator_) {
        declarator_->Print(stream, indent_t(0));
    }
    
    if (value_) {
        stream << " = ";
        value_->Print(stream, indent_t(0));
    }
    
    stream << ";" << std::endl;
}

void Declaration::PrintAsParameter(std::ostream& stream) const
{
    if (type_) {
        type_->Print(stream, indent_t(0));
        stream << " ";
    }
    
    if (declarator_) {
        declarator_->Print(stream, indent_t(0));
    }
    
    // skip semicolon and newline for parameters
}

} // namespace ast