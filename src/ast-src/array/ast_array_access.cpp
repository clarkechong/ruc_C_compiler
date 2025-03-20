#include "ast/array/ast_array_access.hpp"
#include "ast/primary/ast_identifier.hpp"

namespace ast {

ArrayAccess::ArrayAccess() 
    : array_id_(nullptr), index_(nullptr)
{
}

ArrayAccess::ArrayAccess(NodePtr array_id, NodePtr index)
    : array_id_(std::move(array_id)), index_(std::move(index))
{
}

void ArrayAccess::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void ArrayAccess::Print(std::ostream& stream, indent_t indent) const 
{

}

} // namespace ast