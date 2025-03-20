#include "ast/operator/binary_operation/ast_greater_than_eq.hpp"

namespace ast {

GreaterThanEq::GreaterThanEq() 
    : BinaryOperator()
{
}

GreaterThanEq::GreaterThanEq(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void GreaterThanEq::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string left_reg = context.register_manager.AllocateRegister();
    std::string right_reg = context.register_manager.AllocateRegister();
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    left_op_->EmitRISCV(stream, left_reg, context);
    right_op_->EmitRISCV(stream, right_reg, context);
    
    stream << "    slt " << temp_reg << ", " << left_reg << ", " << right_reg << std::endl;
    stream << "    xori " << dst_reg << ", " << temp_reg << ", 1" << std::endl;
    
    context.register_manager.DeallocateRegister(left_reg);
    context.register_manager.DeallocateRegister(right_reg);
    context.register_manager.DeallocateRegister(temp_reg);
}

void GreaterThanEq::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "GreaterThanEq [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
