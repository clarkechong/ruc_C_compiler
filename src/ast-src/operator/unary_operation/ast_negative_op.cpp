#include "ast/operator/unary_operation/ast_negative_op.hpp"

namespace ast {

NegativeOp::NegativeOp() 
    : UnaryOperator()
{
}

NegativeOp::NegativeOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void NegativeOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    op_->EmitRISCV(stream, temp_reg, context);
    
    stream << "    neg " << dst_reg << ", " << temp_reg << std::endl;
    
    context.register_manager.DeallocateRegister(temp_reg);
}

void NegativeOp::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "NegativeOp [" << std::endl;
    op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
