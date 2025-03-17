#include "ast/function/ast_function_definition.hpp"

namespace ast {

FunctionDefinition::FunctionDefinition() 
    : declaration_specifiers_(nullptr), declarator_(nullptr), compound_statement_(nullptr)
{
}

FunctionDefinition::FunctionDefinition(NodePtr declaration_specifiers, NodePtr declarator, NodePtr compound_statement)
    : declaration_specifiers_(std::move(declaration_specifiers)), declarator_(std::move(declarator)), compound_statement_(std::move(compound_statement))
{
}

void FunctionDefinition::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void FunctionDefinition::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent; 
    declaration_specifiers_->Print(stream, 0);
    stream << " ";
    declarator_->Print(stream, 0);
    stream << std::endl;

    compound_statement_->Print(stream, indent);
}

} // namespace ast
