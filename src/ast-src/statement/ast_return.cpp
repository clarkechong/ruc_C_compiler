#include "ast/statement/ast_return.hpp"

namespace ast {

Return::Return() 
    : expr_(nullptr)
{
}

Return::Return(NodePtr expr)
    : expr_(std::move(expr))
{
}

void Return::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Return::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "return";

    if (expr_) {
        stream << " ";
        expr_->Print(stream, 0);
    }
    
    stream << ";" << std::endl;
}

} // namespace ast