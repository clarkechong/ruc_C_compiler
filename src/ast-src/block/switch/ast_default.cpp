#include "ast/block/switch/ast_default.hpp"

namespace ast {

Default::Default() 
    : statement_(nullptr)
{
}

Default::Default(NodePtr statement)
    : statement_(std::move(statement))
{
}

void Default::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string default_label = context.label_manager.CreateLabel("default");
    
    context.label_manager.GetCurrentSwitchReg();
    
    stream << default_label << ":" << std::endl;
    stream << "    # Default case" << std::endl;
    
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
}

void Default::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "Default [" << std::endl;
    
    stream << indent << "Statement:" << std::endl;
    if (statement_) {
        statement_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    
    stream << indent << "]" << std::endl;
}

} // namespace ast