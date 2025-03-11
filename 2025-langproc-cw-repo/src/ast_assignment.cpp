#include "ast_context.hpp"
#include "ast_assignment.hpp"
#include <sstream>

namespace ast {

void Assignment::EmitRISC(std::ostream& stream, Context& context) const
{
    value_->EmitRISC(stream,context);
    //identifier_->EmitRISC(stream,context);
    std::ostringstream interm;
    identifier_->Print(interm);
    std::string name = interm.str();
    int offset = context.GetVariableOffset(name);
    stream << "sw      a5," << offset << "(s0)"<<std::endl;

}

void Assignment::Print(std::ostream& stream) const
{
    //context.AllocateVariable(declarator_,value_);
    identifier_-> Print(stream);
    stream << " = ";
    value_->Print(stream);
    stream << ";"<<std::endl;
}

std::string Assignment::getid() const
{
    return identifier_->getid();
}


} // namespace ast
