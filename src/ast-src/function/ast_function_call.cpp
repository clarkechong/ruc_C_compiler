#include "ast/function/ast_function_call.hpp"

namespace ast {

FunctionCall::FunctionCall() 
    : function_(nullptr), arguments_(nullptr)
{
}

FunctionCall::FunctionCall(NodePtr function, NodePtr arguments)
    : function_(std::move(function)), arguments_(std::move(arguments))
{
}

void FunctionCall::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void FunctionCall::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
