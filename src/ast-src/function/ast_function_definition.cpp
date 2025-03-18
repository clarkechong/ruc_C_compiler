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
    /*
        new scope, reset everything
        << ".section .text" 
        << .globl <id> 
        << .type <id>, @function
    */

    auto func_declarator = dynamic_cast<const FunctionDeclarator*>(declarator_.get());
    if (func_declarator) {
        std::string function_name = func_declarator->GetID();
        stream << ".text" << std::endl;
        stream << ".globl " << function_name << std::endl;
        stream << ".type " << function_name << ", @function" << std::endl;
        stream << function_name << ":" << std::endl;
        compound_statement_->EmitRISCV(stream, dst_reg, context);
        stream << "ret" << std::endl;
    }
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
