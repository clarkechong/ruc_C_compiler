#include "Branch/ast_if.hpp"

namespace ast {

void Ifstate::EmitRISC(std::ostream& stream, Context& context) const
{
    expression_->EmitRISC(stream,context);
    int branchnum = context.Branchoffset();
    stream << "beqz     a5,.L" << branchnum <<std::endl;
    statement_->EmitRISC(stream, context);
    stream << ".L" << branchnum <<":" <<std::endl;


}

void Ifstate::Print(std::ostream& stream) const
{
    stream << "if (";
    expression_->Print(stream);
    stream << "){" <<std::endl;
    statement_->Print(stream);
    stream << std::endl;
    stream << "}" <<std::endl;

}


}
