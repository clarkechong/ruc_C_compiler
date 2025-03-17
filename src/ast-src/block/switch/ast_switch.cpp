#include "ast/block/switch/ast_switch.hpp"

namespace ast {

Switch::Switch() 
    : expression_(nullptr), case_list_(nullptr)
{
}

Switch::Switch(NodePtr expression, NodePtr case_list)
    : expression_(std::move(expression)), case_list_(std::move(case_list))
{
}

void Switch::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Switch::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast