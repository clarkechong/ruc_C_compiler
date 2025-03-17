#include "ast/operator/binary_operation/ast_bitwise_xor.hpp"

namespace ast {

BitwiseXor::BitwiseXor() 
    : BinaryOperator()
{
}

BitwiseXor::BitwiseXor(NodePtr left, NodePtr right)
    : BinaryOperator(std::move(left), std::move(right))
{
}

void BitwiseXor::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void BitwiseXor::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
