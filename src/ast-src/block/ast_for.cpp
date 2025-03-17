#include "ast/block/ast_for.hpp"

namespace ast {

For::For()
: initializer_(nullptr), condition_(nullptr), increment_(nullptr), statement_(nullptr)
{
}

For::For(NodePtr initializer, NodePtr condition, NodePtr increment, NodePtr statement)
: initializer_(std::move(initializer)), condition_(std::move(condition)), increment_(std::move(increment)), statement_(std::move(statement))
{
}

void For::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void For::Print(std::ostream& stream, indent_t indent) const 
{
}

} // namespace ast