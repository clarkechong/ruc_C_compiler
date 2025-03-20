#include "ast/operator/binary_operation/ast_right_shift.hpp"

namespace ast {

RightShift::RightShift() 
    : BinaryOperator()
{
}

RightShift::RightShift(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void RightShift::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string left_reg = context.register_manager.AllocateRegister();
    std::string right_reg = context.register_manager.AllocateRegister();
    
    left_op_->EmitRISCV(stream, left_reg, context);
    right_op_->EmitRISCV(stream, right_reg, context);
    
    stream << "    srl " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
    
    context.register_manager.DeallocateRegister(left_reg);
    context.register_manager.DeallocateRegister(right_reg);
}

void RightShift::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "RightShift [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
