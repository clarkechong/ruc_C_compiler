#include "ast/function/ast_function_definition.hpp"

namespace ast {

FunctionDefinition::FunctionDefinition() 
{
}

void FunctionDefinition::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void FunctionDefinition::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
