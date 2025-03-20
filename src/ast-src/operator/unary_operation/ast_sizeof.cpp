#include "ast/operator/unary_operation/ast_sizeof.hpp"
#include "ast/type/ast_declaration_type.hpp"

namespace ast {

SizeOf::SizeOf()
    : UnaryOperator()
{
}

SizeOf::SizeOf(NodePtr operand)
    : UnaryOperator(std::move(operand))
{
}

void SizeOf::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void SizeOf::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "SizeOf [" << std::endl;
    op_->Print(stream, indent++);
    stream << indent << "]" << std::endl;
}

} // namespace ast
