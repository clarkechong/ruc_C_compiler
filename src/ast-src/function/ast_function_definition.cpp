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
    Declarator* decl = dynamic_cast<Declarator*>(declarator_.get());
    std::string func_name = decl->GetID();

    DeclarationType* type = dynamic_cast<DeclarationType*>(declaration_specifiers_.get());
    TypeSpecifier return_type = type->GetType();

    std::string return_reg = context.register_manager.AllocateReturnRegister(return_type == TypeSpecifier::DOUBLE || return_type == TypeSpecifier::FLOAT);
    
    context.register_manager.ResetRegisters();
    context.stack_manager.ResetFrameOffset();
    
    // push function context (for return statements)
    context.label_manager.PushFunctionContext(func_name);
    std::string end_label = context.label_manager.GetCurrentFunctionEndLabel();
    
    stream << "    .text\n";
    stream << "    .globl " << func_name << "\n";
    stream << "    .type " << func_name << ", @function\n\n";
    
    // the declarator handles printing the function start label
    if (declarator_) { // there should always be a FunctionDeclarator for a function definition...
        declarator_->EmitRISCV(stream, return_reg, context);
    }
    
    if (compound_statement_) {
        compound_statement_->EmitRISCV(stream, return_reg, context);
    }
    
    stream << end_label << ":\n";
    context.scope_manager.ExitScope();
    context.stack_manager.TerminateFrame(stream);
    stream << "    ret\n\n";
    
    context.label_manager.EmitDataSection(stream); // work out if this needs to be done?
    
    // pop function context
    context.label_manager.PopFunctionContext();
}

void FunctionDefinition::Print(std::ostream& stream, indent_t indent) const 
{
    if (declaration_specifiers_) {
        declaration_specifiers_->Print(stream, indent);
        stream << " ";
    }
    
    if (declarator_) {
        declarator_->Print(stream, indent);
    }
    
    // stream << " {\n";
        
    if (compound_statement_) {
        compound_statement_->Print(stream, indent++);
    }
    
    // stream << indent << "}\n";
}

} // namespace ast