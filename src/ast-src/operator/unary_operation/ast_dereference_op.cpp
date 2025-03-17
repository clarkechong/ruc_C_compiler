#include "ast/operator/unary_operation/ast_dereference_op.hpp"

namespace ast {

DereferenceOp::DereferenceOp() 
{
}

void DereferenceOp::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void DereferenceOp::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
