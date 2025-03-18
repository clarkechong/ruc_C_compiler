#include "ast_argdecl.hpp"
#include "ast_context.hpp"
#include <sstream>


namespace ast {

void Argdecl::EmitRISC(std::ostream& stream, Context& context) const
{

    int argie = context.Argreg();
    if(argie < 8){
        expression_->EmitRISC(stream,context);
        stream << "mv       a" << argie << ",a5 " <<std::endl;
    }
    else{
        stream << "how did we get here" <<std::endl;
    }
    // declarator_->EmitRISC(stream,context);

}

void Argdecl::Print(std::ostream& stream) const
{
    expression_->Print(stream);
    stream << ", ";
}



} // namespace ast
