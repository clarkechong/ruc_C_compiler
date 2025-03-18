#include "ast_array.hpp"
#include "ast_context.hpp"
#include <sstream>


namespace ast {

void Array::EmitRISC(std::ostream& stream, Context& context) const
{
    std::ostringstream arraynamestream;
    expression_->Print(arraynamestream);
    std::string arrayname = arraynamestream.str();
    std::ostringstream indexstream;
    index_->Print(indexstream);
    std::string index = indexstream.str();
    int indexint = std::stoi(index);
    std::string nameandindex = arrayname + std::to_string(indexint);
    int offset = context.GetVariableOffset(nameandindex);
    if(offset == 512){
        stream << "lui      a5,%hi("<< arrayname <<")" <<std::endl;
        stream << "addi     a5,a5,%lo(" << arrayname << ")" <<std::endl;
        stream << "lw       a5," <<indexint*4 <<"(a5)" <<std::endl;
    }
    else{
        stream << "lw      a5," << offset << "(s0)"<<std::endl;
    }

}

void Array::Print(std::ostream& stream) const
{
    expression_->Print(stream);
    stream << "[";
    index_->Print(stream);
    stream << "]";
}



} // namespace ast
