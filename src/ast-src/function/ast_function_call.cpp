#include "ast/function/ast_function_call.hpp"

namespace ast {

FunctionCall::FunctionCall() 
{
}

void FunctionCall::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void FunctionCall::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
