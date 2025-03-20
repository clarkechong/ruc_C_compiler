#include "ast/operator/unary_operation/ast_logical_not_op.hpp"

namespace ast {

LogicalNotOp::LogicalNotOp() 
    : UnaryOperator()
{
}

LogicalNotOp::LogicalNotOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void LogicalNotOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    op_->EmitRISCV(stream, temp_reg, context);
    
    stream << "    seqz " << dst_reg << ", " << temp_reg << std::endl;
    
    context.register_manager.DeallocateRegister(temp_reg);
}

void LogicalNotOp::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "LogicalNotOp [" << std::endl;
    op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
