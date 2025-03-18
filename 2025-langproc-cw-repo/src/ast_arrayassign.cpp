#include "ast_context.hpp"
#include "ast_arrayassign.hpp"
#include <sstream>

namespace ast {

void Arrayassign::EmitRISC(std::ostream& stream, Context& context) const
{
    value_->EmitRISC(stream,context);
    std::ostringstream arraynamestream;
    identifier_->Print(arraynamestream);
    std::string arrayname = arraynamestream.str();
    std::ostringstream indexstream;
    index_->Print(indexstream);
    std::string index = indexstream.str();
    int indexint = std::stoi(index);
    std::string nameandindex = arrayname + std::to_string(indexint);
    int offset = context.GetVariableOffset(nameandindex);
    if(offset == 512){
        stream << "lui      a5,%hi("<< arrayname <<")" <<std::endl;
        stream << "addi     a4,a5,%lo(" << arrayname << ")" <<std::endl;
        value_->EmitRISC(stream,context);
        stream << "sw       a5," <<indexint*4 <<"(a4)" <<std::endl;
    }
    else{
        stream << "sw      a5," << offset << "(s0)"<<std::endl;
    }

}

void Arrayassign::Print(std::ostream& stream) const
{
    //context.AllocateVariable(declarator_,value_);
    identifier_-> Print(stream);
    stream << " = ";
    value_->Print(stream);
    stream << ";"<<std::endl;
}

} // namespace ast
