#include "ast/function/ast_function_definition.hpp"
#include "ast/ast_declarator.hpp"

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
    if (!decl) {
        throw std::runtime_error("Function definition has invalid declarator");
    }
    
    std::string func_name = decl->GetID();
    
    context.register_manager.ResetRegisters();
    context.stack_manager.ResetStackPointer();
    context.stack_manager.ResetFramePointer();
    
    // push function context (for return statements)
    context.label_manager.PushFunctionContext(func_name);
    std::string end_label = context.label_manager.GetCurrentFunctionEndLabel();
    
    stream << "    .text\n";
    stream << "    .globl " << func_name << "\n";
    stream << "    .type " << func_name << ", @function\n\n";
    
    // emit function declarator - this will create function label and setup stack
    if (declarator_) {
        declarator_->EmitRISCV(stream, dst_reg, context);
    }
    
    if (compound_statement_) {
        compound_statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << end_label << ":\n";
    context.stack_manager.TerminateFrame(stream);
    stream << "    ret\n\n";
    
    context.label_manager.EmitDataSection(stream);
    
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