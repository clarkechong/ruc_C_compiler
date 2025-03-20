#include "ast/block/ast_while.hpp"

namespace ast {

While::While()
: condition_(nullptr), statement_(nullptr)
{
}

While::While(NodePtr condition, NodePtr statement)
: condition_(std::move(condition)), statement_(std::move(statement))
{
}

void While::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string condition_reg = context.register_manager.AllocateRegister();
    std::string start_label = context.label_manager.CreateLabel("while_start");
    std::string body_label = context.label_manager.CreateLabel("while_body");
    std::string end_label = context.label_manager.CreateLabel("while_end");
    
    context.label_manager.PushLoopStart(start_label);
    context.label_manager.PushLoopUpdate(start_label);
    context.label_manager.PushLoopEnd(end_label);
    
    stream << "    j " << start_label << std::endl;
    
    stream << body_label << ":" << std::endl;
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << start_label << ":" << std::endl;
    condition_->EmitRISCV(stream, condition_reg, context);
    stream << "    bnez " << condition_reg << ", " << body_label << std::endl;
    
    stream << end_label << ":" << std::endl;
    
    context.label_manager.PopLoopStart();
    context.label_manager.PopLoopUpdate();
    context.label_manager.PopLoopEnd();
    
    context.register_manager.DeallocateRegister(condition_reg);
}

void While::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "While [" << std::endl;
    stream << indent << "Condition:" << std::endl;
    if (condition_) {
        condition_->Print(stream, indent++);
    }
    stream << indent << "Statement:" << std::endl;
    if (statement_) {
        statement_->Print(stream, indent++);
    }
    stream << indent << "]" << std::endl;
}

} // namespace ast
