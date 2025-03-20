#include "ast/operator/binary_operation/ast_logical_or.hpp"

namespace ast {

LogicalOr::LogicalOr() 
    : BinaryOperator()
{
}

LogicalOr::LogicalOr(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void LogicalOr::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    TypeSpecifier type = TypeSpecifier::INT;
    
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    std::string label1 = context.label_manager.CreateLabel("LOGICAL_OR");
    std::string label2 = context.label_manager.CreateLabel("LOGICAL_OR");
    std::string label_end = context.label_manager.CreateLabel("LOGICAL_OR");
    
    left_op_->EmitRISCV(stream, temp_reg, context);
    stream << "    bne " << temp_reg << ", zero, " << label1 << std::endl;
    
    right_op_->EmitRISCV(stream, temp_reg, context);
    stream << "    beq " << temp_reg << ", zero, " << label2 << std::endl;
    
    stream << label1 << ":" << std::endl;
    stream << "    li " << temp_reg << ", 1" << std::endl;
    stream << "    j " << label_end << std::endl;
    
    stream << label2 << ":" << std::endl;
    stream << "    li " << temp_reg << ", 0" << std::endl;
    
    stream << label_end << ":" << std::endl;
    stream << "    mv " << dst_reg << ", " << temp_reg << std::endl;
    
    context.register_manager.DeallocateRegister(temp_reg);
}

void LogicalOr::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "LogicalOr [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
