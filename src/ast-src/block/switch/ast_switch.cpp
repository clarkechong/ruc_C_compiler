#include "ast/block/switch/ast_switch.hpp"
#include "ast/block/switch/ast_case.hpp"
#include "ast/block/switch/ast_default.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/statement/ast_break.hpp"

namespace ast {

Switch::Switch() 
    : expression_(nullptr), statement_(nullptr)
{
}

Switch::Switch(NodePtr expression, NodePtr statement)
    : expression_(std::move(expression)), statement_(std::move(statement))
{
}

void Switch::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string end_label = context.label_manager.CreateLabel("switch_end");
    context.label_manager.PushLoopEnd(end_label); // for handling break statements

    stream << "    # Switch statement" << std::endl;
    std::string switch_reg = context.register_manager.AllocateRegister();
    expression_->EmitRISCV(stream, switch_reg, context);
    
    context.label_manager.PushSwitchContext(switch_reg);
    
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    stream << end_label << ":" << std::endl;
    
    context.register_manager.DeallocateRegister(switch_reg);
    context.label_manager.PopSwitchContext();
    context.label_manager.PopLoopEnd();
}

void Switch::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "Switch [" << std::endl;
    
    stream << indent << "Expression:" << std::endl;
    if (expression_) {
        expression_->Print(stream, indent++);
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