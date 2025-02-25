#include "ast_variable.hpp"

namespace ast {

void Variable::EmitRISC(std::ostream& stream, Context& context) const
{
    int offset = context.GetVariableOffset(name_);
    stream << "lw t0, " << offset << "(sp)" <<std::endl;
}

void Variable::Print(std::ostream& stream) const
{
    stream << name_;
}

int Variable::GetValue(const SymbolTable& table) const {
    return table.GetValue(name_);
}
const std::string Variable::GetName() const { return name_; }

} // namespace ast
