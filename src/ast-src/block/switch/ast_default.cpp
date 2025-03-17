#include "ast/block/switch/ast_default.hpp"

namespace ast {

Default::Default() 
{
}

void Default::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Default::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast