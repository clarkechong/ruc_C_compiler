#include "Branch/ast_if.hpp"

namespace ast {

void EILF::EmitRISC(std::ostream& stream, Context& context) const
{
    condexpression_->EmitRISC(stream,context);
    int branchnumi = context.Branchoffset();
    stream << "beqz     a5,.L" << branchnumi <<std::endl;
    ifstatement_->EmitRISC(stream, context);
    int branchnume = context.Branchoffset();
    if(elsestatement_ != nullptr){
        stream << "j        .L" <<branchnume <<std::endl;
    }
    stream << ".L" << branchnumi <<":" <<std::endl;
    if(elsestatement_ != nullptr){
        elsestatement_->EmitRISC(stream,context);
        stream << ".L" << branchnume << ":" <<std::endl;
    }
}

void EILF::Print(std::ostream& stream) const
{
    stream << "if (";
    condexpression_->Print(stream);
    stream << "){" <<std::endl;
    ifstatement_->Print(stream);
    stream << "}" <<std::endl;
    if(elsestatement_ != nullptr){
        stream << "else{" <<std::endl;
        elsestatement_->Print(stream);
        stream << "}" << std::endl;
    }

}


}
