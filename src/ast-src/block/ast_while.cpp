#include "ast/block/ast_while.hpp"

namespace ast {

While::While()
: condition_(nullptr), statement_(nullptr)
{
}

While::While(NodePtr condition, NodePtr statement)
: condition_(std::move(condition)), statement_(std::move(statement))
{
}

void While::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void While::Print(std::ostream& stream, int indent) const 
{
}

} // namespace ast
