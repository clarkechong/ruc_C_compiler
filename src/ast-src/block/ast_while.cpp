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
    std::string loop_start_label = context.label_manager.CreateLabel("while_start");
    std::string loop_cond_label = context.label_manager.CreateLabel("while_cond");
    std::string loop_end_label = context.label_manager.CreateLabel("while_end");
    
    context.label_manager.PushLoopStart(loop_cond_label);
    context.label_manager.PushLoopEnd(loop_end_label);
    stream << "    j " << loop_cond_label << std::endl;
    stream << loop_start_label << ":" << std::endl;
    
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << loop_cond_label << ":" << std::endl;
    
    if (condition_) {
        std::string cond_reg = context.register_manager.AllocateRegister();
        condition_->EmitRISCV(stream, cond_reg, context);
        
        stream << "    bnez " << cond_reg << ", " << loop_start_label << std::endl;
        context.register_manager.DeallocateRegister(cond_reg);
    } else {
        stream << "    j " << loop_start_label << std::endl;
    }
    
    stream << loop_end_label << ":" << std::endl;
    
    context.label_manager.PopLoopEnd();
    context.label_manager.PopLoopStart();
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
