#include "ast/operator/unary_operation/ast_dereference_op.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

DereferenceOp::DereferenceOp() 
{
}

DereferenceOp::DereferenceOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void DereferenceOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    std::string ptr_reg = context.register_manager.AllocateRegister();
    op_->EmitRISCV(stream, ptr_reg, context); // store the memory address the ptr holds
    
    std::string load_inst = "lw"; // determine this from context?
    
    stream << "    # Dereferencing pointer" << std::endl;
    stream << "    " << load_inst << " " << dst_reg << ", 0(" << ptr_reg << ")" << std::endl;
    
    context.register_manager.DeallocateRegister(ptr_reg);
}

void DereferenceOp::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "DereferenceOp [" << std::endl;
    if (op_) {
        op_->Print(stream, indent++);
    } else {
        stream << indent++ << "null" << std::endl;
    }
    stream << indent << "]" << std::endl;
}

} // namespace ast
