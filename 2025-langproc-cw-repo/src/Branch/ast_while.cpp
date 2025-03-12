#include "Branch/ast_while.hpp"

namespace ast {

void Whilefunc::EmitRISC(std::ostream& stream, Context& context) const
{
    int checkloop = context.Branchoffset();
    stream << "j        .L" << checkloop << std::endl;
    int executeloop = context.Branchoffset();
    stream << ".L" << executeloop << ":" <<std::endl;
    statement_->EmitRISC(stream,context);
    stream << ".L" << checkloop << ":" <<std::endl;
    condexpression_->EmitRISC(stream,context);
    stream << "bnez     a5,.L" << executeloop <<std::endl;
}

void Whilefunc::Print(std::ostream& stream) const
{
    stream << "while (";
    condexpression_->Print(stream);
    stream << ") {" << std::endl;
    statement_->Print(stream);
    stream << "}" <<std::endl;
}


}
