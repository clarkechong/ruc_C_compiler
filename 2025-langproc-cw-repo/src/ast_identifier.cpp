#include "ast_identifier.hpp"
#include "ast_context.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, Context& context) const
{

    int offset = context.GetVariableOffset(identifier_);
    stream << "lw      a5," << offset << "(s0)"<<std::endl;
}

void Identifier::Print(std::ostream& stream) const
{
    stream << identifier_;
};


}
