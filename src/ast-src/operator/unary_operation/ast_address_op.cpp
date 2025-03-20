#include "ast/operator/unary_operation/ast_address_op.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

AddressOp::AddressOp() 
    : UnaryOperator()
{
}

AddressOp::AddressOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void AddressOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    const auto* id = dynamic_cast<const Identifier*>(op_.get());
    
    if (id) {
        std::string var_id = id->GetID();
        
        if (!context.scope_manager.VariableExists(var_id)) {
            throw std::runtime_error("cannot take address of undeclared variable '" + var_id + "'");
        }
        
        Variable_s var = context.scope_manager.GetVariable(var_id);
        
        if (context.scope_manager.InGlobalScope()) {
            stream << "    la " << dst_reg << ", " << var_id << std::endl;
        } else {
            stream << "    addi " << dst_reg << ", s0, " << var.stack_offset << std::endl;
        }
    }
}

void AddressOp::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "AddressOp [" << std::endl;
    op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
