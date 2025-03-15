#include "ast_paramdecl.hpp"
#include "ast_context.hpp"
#include <sstream>


namespace ast {

void ParamDecl::EmitRISC(std::ostream& stream, Context& context) const
{
    std::ostringstream badworkaround;
    declarator_->Print(badworkaround);
    std::string name = badworkaround.str();
    context.AllocateVariable(name);
    int offset = context.GetVariableOffset(name);
   // stream << " param" << offset <<std::endl;
    int reggie = context.Paramreg();
    if(reggie < 8){
        stream << "sw       a" << reggie << "," << offset << "(s0)" <<std::endl;
    }
    // declarator_->EmitRISC(stream,context);

}

void ParamDecl::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";
    declarator_->Print(stream);
    stream << ", ";
}



} // namespace ast
