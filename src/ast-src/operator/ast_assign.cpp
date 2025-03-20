#include "ast/operator/ast_assign.hpp"

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
    auto declarator = dynamic_cast<const Declarator*>(left_op_.get());
    if (!declarator) throw std::runtime_error("couldnt cast to declarator in Assign:EmitRISCV :(");
    
    std::string id = declarator->GetID();
    std::string temp_reg = context.register_manager.AllocateRegister();
    
    right_op_->EmitRISCV(stream, temp_reg, context);
    
    context.stack_manager.StoreRegisterToVariable(stream, temp_reg, id);
    
    if (dst_reg != temp_reg) {
        stream << "    mv " << dst_reg << ", " << temp_reg << std::endl;
    }
    
    context.register_manager.DeallocateRegister(temp_reg);
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
