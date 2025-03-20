#include "ast/block/switch/ast_case.hpp"
#include "ast/primary/ast_integer.hpp"

namespace ast {

Case::Case() 
    : expression_(nullptr), statement_(nullptr)
{
}

Case::Case(NodePtr expression, NodePtr statement)
    : expression_(std::move(expression)), statement_(std::move(statement))
{
}

void Case::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string case_label = context.label_manager.CreateLabel("case");
    std::string next_case_label = context.label_manager.CreateLabel("next_case");
    
    std::string value_reg = context.register_manager.AllocateRegister();
    expression_->EmitRISCV(stream, value_reg, context);
    
    std::string switch_reg = context.label_manager.GetCurrentSwitchReg();
    
    stream << "    # Case comparison" << std::endl;
    stream << "    bne " << switch_reg << ", " << value_reg << ", " << next_case_label << std::endl;
    
    stream << case_label << ":" << std::endl;
    if (statement_) {
        statement_->EmitRISCV(stream, dst_reg, context);
    }
    
    
    stream << next_case_label << ":" << std::endl;

    
    context.register_manager.DeallocateRegister(value_reg);
}

void Case::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "Case [" << std::endl;
    
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