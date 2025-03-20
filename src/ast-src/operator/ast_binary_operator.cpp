#include "ast/operator/ast_binary_operator.hpp"
#include "ast/primary/ast_float.hpp"
#include "ast/primary/ast_integer.hpp"
#include "ast/primary/ast_identifier.hpp"

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
    // Base implementation is empty
}

void BinaryOperator::Print(std::ostream& stream, indent_t indent) const 
{
    // Base implementation is empty
}

std::tuple<bool, bool> BinaryOperator::CheckOperandTypes(Context& context) const 
{
    bool is_float = false;
    bool is_double = false;
    
    // Check left operand
    if (dynamic_cast<Float*>(left_op_.get())) {
        is_float = true;
    } else if (auto* id = dynamic_cast<Identifier*>(left_op_.get())) {
        try {
            Variable_s var = context.scope_manager.GetVariable(id->GetID());
            if (var.type == TypeSpecifier::FLOAT) is_float = true;
            else if (var.type == TypeSpecifier::DOUBLE) is_double = true;
        } catch (const std::runtime_error&) {}
    }
    
    // Check right operand
    if (dynamic_cast<Float*>(right_op_.get())) {
        is_float = true;
    } else if (auto* id = dynamic_cast<Identifier*>(right_op_.get())) {
        try {
            Variable_s var = context.scope_manager.GetVariable(id->GetID());
            if (var.type == TypeSpecifier::FLOAT) is_float = true;
            else if (var.type == TypeSpecifier::DOUBLE) is_double = true;
        } catch (const std::runtime_error&) {}
    }
    
    return std::make_tuple(is_float, is_double);
}

} // namespace ast
