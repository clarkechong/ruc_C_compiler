#include "ast/operator/binary_operation/ast_not_equal.hpp"
#include "ast/primary/ast_float.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

NotEqual::NotEqual() 
    : BinaryOperator()
{
}

NotEqual::NotEqual(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void NotEqual::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    auto [is_float, is_double] = CheckOperandTypes(context);
    
    if (is_float || is_double) {
        std::string left_reg = context.register_manager.AllocateRegister(true);
        std::string right_reg = context.register_manager.AllocateRegister(true);
        std::string temp_reg = context.register_manager.AllocateRegister();
        
        left_op_->EmitRISCV(stream, left_reg, context);
        right_op_->EmitRISCV(stream, right_reg, context);
        
        if (is_double)
            stream << "    feq.d " << temp_reg << ", " << left_reg << ", " << right_reg << std::endl;
        else
            stream << "    feq.s " << temp_reg << ", " << left_reg << ", " << right_reg << std::endl;
            
        stream << "    xori " << dst_reg << ", " << temp_reg << ", 1" << std::endl;
        
        context.register_manager.DeallocateRegister(left_reg);
        context.register_manager.DeallocateRegister(right_reg);
        context.register_manager.DeallocateRegister(temp_reg);
    } else {
        std::string left_reg = context.register_manager.AllocateRegister();
        std::string right_reg = context.register_manager.AllocateRegister();
        
        left_op_->EmitRISCV(stream, left_reg, context);
        right_op_->EmitRISCV(stream, right_reg, context);
        
        stream << "    xor " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        stream << "    snez " << dst_reg << ", " << dst_reg << std::endl;
        
        context.register_manager.DeallocateRegister(left_reg);
        context.register_manager.DeallocateRegister(right_reg);
    }
}

void NotEqual::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "NotEqual [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
