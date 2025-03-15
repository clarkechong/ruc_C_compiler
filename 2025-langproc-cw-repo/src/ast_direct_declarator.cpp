#include "ast_direct_declarator.hpp"

namespace ast {

void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context) const
{
    identifier_->Print(stream);
    stream << " " <<std::endl;
    identifier_->Print(stream);
    stream << ":" <<std::endl;
    stream << "addi    sp,sp,-100" <<std::endl;
    stream << "sw      ra,96(sp)" <<std::endl;
    stream << "sw      s0,92(sp)" <<std::endl;
    stream << "addi    s0,sp,100" <<std::endl;
    if(param_list_ != nullptr){
        param_list_->EmitRISC(stream, context);
    }
}

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
    if (param_list_ != nullptr){
        stream << "(";
        param_list_->Print(stream);
        stream << ") {" <<std::endl;
    }
}



} // namespace ast
