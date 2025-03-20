#include "ast/block/ast_if_else.hpp"

namespace ast {

IfElse::IfElse()
: condition_(nullptr), if_statement_(nullptr), else_statement_(nullptr)
{
}

IfElse::IfElse(NodePtr condition, NodePtr if_statement, NodePtr else_statement)
: condition_(std::move(condition)), if_statement_(std::move(if_statement)), else_statement_(std::move(else_statement))
{
}

void IfElse::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string condition_reg = context.register_manager.AllocateRegister();
    std::string else_label = context.label_manager.CreateLabel("if_else");
    std::string end_label = context.label_manager.CreateLabel("if_end");
    
    condition_->EmitRISCV(stream, condition_reg, context);
    stream << "    beqz " << condition_reg << ", " << else_label << std::endl;
    
    if (if_statement_) {
        if_statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    if (else_statement_) {
        stream << "    j " << end_label << std::endl;
    }
    
    stream << else_label << ":" << std::endl;
    if (else_statement_) {
        else_statement_->EmitRISCV(stream, dst_reg, context);
        stream << end_label << ":" << std::endl;
    }
    
    context.register_manager.DeallocateRegister(condition_reg);
}

void IfElse::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "IfElse [" << std::endl;
    stream << indent << "Condition:" << std::endl;
    if (condition_) {
        condition_->Print(stream, indent++);
    }
    stream << indent << "If Statement:" << std::endl;
    if (if_statement_) {
        if_statement_->Print(stream, indent++);
    }
    stream << indent << "Else Statement:" << std::endl;
    if (else_statement_) {
        else_statement_->Print(stream, indent++);
    }
    stream << indent << "]" << std::endl;
}

} // namespace ast
