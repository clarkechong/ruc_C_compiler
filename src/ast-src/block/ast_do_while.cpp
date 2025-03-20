#include "ast/block/ast_do_while.hpp"

namespace ast {

DoWhile::DoWhile()
: statement_(nullptr), condition_(nullptr)
{
}

DoWhile::DoWhile(NodePtr statement, NodePtr condition)
: statement_(std::move(statement)), condition_(std::move(condition))
{
}

void DoWhile::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string start_label = context.label_manager.CreateLabel("do_while");
    std::string condition_label = context.label_manager.CreateLabel("do_while_cond");
    std::string end_label = context.label_manager.CreateLabel("do_while_end");
    
    std::string condition_reg = context.register_manager.AllocateRegister();
    
    context.label_manager.PushLoopStart(start_label);
    context.label_manager.PushLoopUpdate(condition_label);
    context.label_manager.PushLoopEnd(end_label);
    
    stream << start_label << ":" << std::endl;
    
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << condition_label << ":" << std::endl;
    condition_->EmitRISCV(stream, condition_reg, context);
    
    stream << "    bnez " << condition_reg << ", " << start_label << std::endl;
    
    stream << end_label << ":" << std::endl;
    
    context.label_manager.PopLoopStart();
    context.label_manager.PopLoopUpdate();
    context.label_manager.PopLoopEnd();
    
    context.register_manager.DeallocateRegister(condition_reg);
}

void DoWhile::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "DoWhile [" << std::endl;
    stream << indent << "Statement:" << std::endl;
    if (statement_) {
        statement_->Print(stream, indent++);
    }
    stream << indent << "Condition:" << std::endl;
    if (condition_) {
        condition_->Print(stream, indent++);
    }
    stream << indent << "]" << std::endl;
}

} // namespace ast