#include "ast/operator/ast_binary_operator.hpp"

namespace ast {

BinaryOperator::BinaryOperator() 
    : left_op_(nullptr), right_op_(nullptr)
{
}

BinaryOperator::BinaryOperator(NodePtr left_op, NodePtr right_op)
    : left_op_(std::move(left_op)), right_op_(std::move(right_op))
{
}

void BinaryOperator::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void BinaryOperator::Print(std::ostream& stream, indent_t indent) const 
{

}

} // namespace ast
