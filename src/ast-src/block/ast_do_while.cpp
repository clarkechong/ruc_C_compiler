#include "ast/block/ast_do_while.hpp"

namespace ast {

DoWhile::DoWhile(NodePtr condition, NodePtr statement)
: condition_(std::move(condition)), statement_(std::move(statement)) {}

void DoWhile::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void DoWhile::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast