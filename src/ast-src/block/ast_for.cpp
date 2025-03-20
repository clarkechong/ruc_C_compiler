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
    std::string start_label = context.label_manager.CreateLabel("for_start");
    std::string iteration_label = context.label_manager.CreateLabel("for_iteration");
    std::string end_label = context.label_manager.CreateLabel("for_end");
    
    context.label_manager.PushLoopUpdate(iteration_label);
    context.label_manager.PushLoopEnd(end_label);
    
    std::string loop_reg = context.register_manager.AllocateRegister();
    
    stream << init_label << ":" << std::endl;
    if (initializer_) {
        initializer_->EmitRISCV(stream, loop_reg, context);
    }
    
    stream << start_label << ":" << std::endl;
    
    if (condition_) {
        condition_->EmitRISCV(stream, loop_reg, context);
        stream << "    beqz " << loop_reg << ", " << end_label << std::endl;
    }
    
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << iteration_label << ":" << std::endl;
    if (increment_) {
        increment_->EmitRISCV(stream, loop_reg, context);
    }
    
    stream << "    j " << start_label << std::endl;
    stream << end_label << ":" << std::endl;
    
    context.label_manager.PopLoopEnd();
    context.label_manager.PopLoopUpdate();
    context.register_manager.DeallocateRegister(loop_reg);
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