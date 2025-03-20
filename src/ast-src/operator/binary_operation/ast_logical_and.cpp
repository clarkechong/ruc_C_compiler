#include "ast/operator/binary_operation/ast_logical_and.hpp"

namespace ast {

LogicalAnd::LogicalAnd() 
    : BinaryOperator()
{
}

LogicalAnd::LogicalAnd(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LogicalAnd::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string left_reg = context.register_manager.AllocateRegister();
    std::string right_reg = context.register_manager.AllocateRegister();
    std::string end_label = context.label_manager.CreateLabel("and_end");
    
    left_op_->EmitRISCV(stream, left_reg, context);
    
    stream << "    beqz " << left_reg << ", " << end_label << std::endl;
    
    right_op_->EmitRISCV(stream, right_reg, context);
    
    stream << "    snez " << dst_reg << ", " << right_reg << std::endl;
    stream << "    j " << end_label << std::endl;
    stream << end_label << ":" << std::endl;
    stream << "    li " << dst_reg << ", 0" << std::endl;
    
    context.register_manager.DeallocateRegister(left_reg);
    context.register_manager.DeallocateRegister(right_reg);
}

void LogicalAnd::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "LogicalAnd [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
