#include "ast/operator/binary_operation/ast_multiply.hpp"
#include "ast/primary/ast_float.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

Multiply::Multiply() 
    : BinaryOperator()
{
}

Multiply::Multiply(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Multiply::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    bool is_float = false;
    bool is_double = false;
    
    if (dynamic_cast<Float*>(left_op_.get())) is_float = true;
    else if (dynamic_cast<Identifier*>(left_op_.get())) {
        try {
            Variable_s var = context.scope_manager.GetVariable(dynamic_cast<Identifier*>(left_op_.get())->GetID());
            if (var.type == TypeSpecifier::FLOAT) is_float = true;
            else if (var.type == TypeSpecifier::DOUBLE) is_double = true;
        } catch (const std::runtime_error&) {}
    }
    
    if (dynamic_cast<Float*>(right_op_.get())) is_float = true;
    else if (dynamic_cast<Identifier*>(right_op_.get())) {
        try {
            Variable_s var = context.scope_manager.GetVariable(dynamic_cast<Identifier*>(right_op_.get())->GetID());
            if (var.type == TypeSpecifier::FLOAT) is_float = true;
            else if (var.type == TypeSpecifier::DOUBLE) is_double = true;
        } catch (const std::runtime_error&) {}
    }

    if (is_float || is_double) {
        std::string left_reg = context.register_manager.AllocateRegister(true);
        std::string right_reg = context.register_manager.AllocateRegister(true);
        
        left_op_->EmitRISCV(stream, left_reg, context);
        right_op_->EmitRISCV(stream, right_reg, context);
        
        if (is_double)
            stream << "    fmul.d " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        else
            stream << "    fmul.s " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        
        context.register_manager.DeallocateRegister(left_reg);
        context.register_manager.DeallocateRegister(right_reg);
    } else {
        std::string left_reg = context.register_manager.AllocateRegister();
        std::string right_reg = context.register_manager.AllocateRegister();
        
        left_op_->EmitRISCV(stream, left_reg, context);
        right_op_->EmitRISCV(stream, right_reg, context);
        
        stream << "    mul " << dst_reg << ", " << left_reg << ", " << right_reg << std::endl;
        
        context.register_manager.DeallocateRegister(left_reg);
        context.register_manager.DeallocateRegister(right_reg);
    }
}

void Multiply::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "Multiply [" << std::endl;
    left_op_->Print(stream, indent++);
    right_op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
