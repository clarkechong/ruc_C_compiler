#include "ast/operator/unary_operation/ast_bitwise_not_op.hpp"

namespace ast {

BitwiseNotOp::BitwiseNotOp() 
    : UnaryOperator()
{
}

BitwiseNotOp::BitwiseNotOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void BitwiseNotOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    op_->EmitRISCV(stream, temp_reg, context);
    
    stream << "    not " << dst_reg << ", " << temp_reg << std::endl;
    
    context.register_manager.DeallocateRegister(temp_reg);
}

void BitwiseNotOp::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "BitwiseNotOp [" << std::endl;
    op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
