#include "ast/operator/binary_operation/ast_add.hpp"
#include "ast/primary/ast_float.hpp"
#include "ast/primary/ast_integer.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

Add::Add() 
    : BinaryOperator()
{
}

Add::Add(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Add::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    auto [is_float, is_double] = CheckOperandTypes(context);

    if (is_float || is_double) {
        std::string left_reg = context.register_manager.AllocateRegister(true);
        std::string right_reg = context.register_manager.AllocateRegister(true);
        
        left_op_->EmitRISCV(stream, left_reg, context);
        right_op_->EmitRISCV(stream, right_reg, context);
        
        if (is_double)
            stream << "    fadd.d " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        else
            stream << "    fadd.s " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        
        context.register_manager.DeallocateRegister(left_reg);
        context.register_manager.DeallocateRegister(right_reg);
    } else {
        std::string left_reg = context.register_manager.AllocateRegister();
        std::string right_reg = context.register_manager.AllocateRegister();
        
        left_op_->EmitRISCV(stream, left_reg, context);
        right_op_->EmitRISCV(stream, right_reg, context);
        
        stream << "    add " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        
        context.register_manager.DeallocateRegister(left_reg);
        context.register_manager.DeallocateRegister(right_reg);
    }
}

void Add::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "Add [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
