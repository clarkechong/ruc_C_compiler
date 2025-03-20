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
    // stream << "    # DEBUG: Left operand type: " << typeid(*expr_).name() << std::endl;
    if (expr_) {
        expr_->EmitRISCV(stream, dst_reg, context);
    }
    
    std::string end_label = context.label_manager.GetCurrentFunctionEndLabel();
    stream << "    j " << end_label << "\n";
}

void Return::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "return";
    
    if (expr_) {
        stream << " ";
        expr_->Print(stream, indent_t(0));
    }
    
    stream << ";\n";
}

} // namespace ast