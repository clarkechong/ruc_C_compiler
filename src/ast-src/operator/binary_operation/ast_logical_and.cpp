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
    TypeSpecifier type = TypeSpecifier::INT;
    
    std::string label1 = context.label_manager.CreateLabel("LOGICAL_AND");
    std::string label2 = context.label_manager.CreateLabel("LOGICAL_AND");
    
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    left_op_->EmitRISCV(stream, temp_reg, context);
    stream << "    beq " << temp_reg << ", zero, " << label1 << std::endl;
    
    right_op_->EmitRISCV(stream, temp_reg, context);
    stream << "    beq " << temp_reg << ", zero, " << label1 << std::endl;
    
    stream << "    li " << dst_reg << ", 1" << std::endl;
    stream << "    j " << label2 << std::endl;
    
    stream << label1 << ":" << std::endl;
    stream << "    li " << dst_reg << ", 0" << std::endl;
    
    stream << label2 << ":" << std::endl;
    
    context.register_manager.DeallocateRegister(temp_reg);
}

void LogicalAnd::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "LogicalAnd [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
