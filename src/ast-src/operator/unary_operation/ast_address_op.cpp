#include "ast/operator/unary_operation/ast_address_op.hpp"

namespace ast {

AddressOp::AddressOp() 
{
}

AddressOp::AddressOp(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void AddressOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void AddressOp::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast
