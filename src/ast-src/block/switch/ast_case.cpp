#include "ast/block/switch/ast_case.hpp"

namespace ast {

Case::Case() 
{
}

void Case::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Case::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast