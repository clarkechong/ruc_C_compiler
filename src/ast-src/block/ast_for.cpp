#include "ast/block/ast_for.hpp"

namespace ast {

For::For()
: initializer_(nullptr), condition_(nullptr), increment_(nullptr), statement_(nullptr)
{
}

For::For(NodePtr initializer, NodePtr condition, NodePtr increment, NodePtr statement)
: initializer_(std::move(initializer)), condition_(std::move(condition)), increment_(std::move(increment)), statement_(std::move(statement))
{
}

void For::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string init_label = context.label_manager.CreateLabel("for_init");
    std::string cond_label = context.label_manager.CreateLabel("for_cond");
    std::string body_label = context.label_manager.CreateLabel("for_body");
    std::string incr_label = context.label_manager.CreateLabel("for_incr");
    std::string end_label = context.label_manager.CreateLabel("for_end");
    
    std::string cond_reg = context.register_manager.AllocateRegister();
    
    context.label_manager.PushLoopStart(cond_label);
    context.label_manager.PushLoopUpdate(incr_label);
    context.label_manager.PushLoopEnd(end_label);
    
    stream << init_label << ":" << std::endl;
    if (initializer_) {
        initializer_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << "    j " << cond_label << std::endl;
    
    stream << body_label << ":" << std::endl;
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << incr_label << ":" << std::endl;
    if (increment_) {
        increment_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << cond_label << ":" << std::endl;
    if (condition_) {
        condition_->EmitRISCV(stream, cond_reg, context);
        stream << "    bnez " << cond_reg << ", " << body_label << std::endl;
    } else {
        stream << "    j " << body_label << std::endl;
    }
    
    stream << end_label << ":" << std::endl;
    
    context.label_manager.PopLoopStart();
    context.label_manager.PopLoopUpdate();
    context.label_manager.PopLoopEnd();
    
    context.register_manager.DeallocateRegister(cond_reg);
}

void For::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "For [" << std::endl;
    
    stream << indent << "Initializer:" << std::endl;
    if (initializer_) {
        initializer_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "Condition:" << std::endl;
    if (condition_) {
        condition_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "Increment:" << std::endl;
    if (increment_) {
        increment_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "Statement:" << std::endl;
    if (statement_) {
        statement_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "]" << std::endl;
}

} // namespace ast