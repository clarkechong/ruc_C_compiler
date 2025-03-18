#include "ast/statement/ast_return.hpp"

namespace ast {

Return::Return() 
    : return_node_(nullptr)
{
}

Return::Return(NodePtr return_node)
    : return_node_(std::move(return_node))
{
}

void Return::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
    if(return_node_) return_node_->EmitRISCV(stream, dst_reg, context);
    // return to end of function label, after which is ret instruction
}

void Return::Print(std::ostream& stream, indent_t indent) const 
{
    stream << indent << "return";

    if (return_node_) {
        stream << " ";
        return_node_->Print(stream, 0);
    }
    
    stream << ";" << std::endl;
}

} // namespace ast