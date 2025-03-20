#include "ast/operator/ast_assign.hpp"
#include "ast/array/ast_array_declarator.hpp"
#include "ast/primary/ast_identifier.hpp"
#include "ast/primary/ast_integer.hpp"
#include "ast/operator/unary_operation/ast_dereference_op.hpp"

namespace ast {

Assign::Assign() 
    : BinaryOperator()
{
}

Assign::Assign(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void Assign::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string value_reg = context.register_manager.AllocateRegister();
    right_op_->EmitRISCV(stream, value_reg, context);
    
    if (dst_reg != value_reg) {
        stream << "    mv " << dst_reg << ", " << value_reg << std::endl; // only to set return value
    }

    stream << "    # DEBUG: LEFT operand type: " << typeid(*left_op_).name() << std::endl;
    stream << "    # DEBUG: RIGHT operand type: " << typeid(*right_op_).name() << std::endl;

    auto identifier = dynamic_cast<const Identifier*>(left_op_.get());
    auto arraydeclarator = dynamic_cast<const ArrayDeclarator*>(left_op_.get());
    auto dereference = dynamic_cast<const DereferenceOp*>(left_op_.get());

    if (identifier) {
        std::string var_id = identifier->GetID();
        stream << "    # Assigning to variable: " << var_id << std::endl;
        context.stack_manager.StoreRegisterToVariable(stream, value_reg, var_id);
    }
    else if (arraydeclarator) {
        std::string var_id = arraydeclarator->GetID();
        stream << "    # Assigning to array variable: " << var_id << std::endl;
        context.stack_manager.StoreRegisterToVariable(stream, value_reg, var_id, false, true, arraydeclarator->GetArrayIndexSpecifiers());
    }
    else {
    }
    
    context.register_manager.DeallocateRegister(value_reg);
}

void Assign::Print(std::ostream& stream, indent_t indent) const 
{
    if (left_op_ && right_op_) {
        left_op_->Print(stream, indent);
        stream << " = ";
        right_op_->Print(stream, indent);
    }
}

} // namespace ast
