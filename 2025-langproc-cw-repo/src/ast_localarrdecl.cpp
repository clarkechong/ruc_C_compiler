#include "ast_localarrdecl.hpp"
#include "ast_context.hpp"
#include <sstream>


namespace ast {

void Localarrdecl::EmitRISC(std::ostream& stream, Context& context) const
{
    std::ostringstream arraynamestream;
    declarator_->Print(arraynamestream);
    std::string arrayname = arraynamestream.str();
    std::ostringstream sizestream;
    size_->Print(sizestream);
    std::string size = sizestream.str();
    int sizeint = std::stoi(size);
    std::string nameandindex;
    for(int i = 0; i < sizeint; i++){
        nameandindex = arrayname + std::to_string(i);
        context.AllocateVariable(nameandindex);
    }
    stream << " " <<std::endl;

}

void Localarrdecl::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";
    declarator_->Print(stream);
    stream << "[";
    size_->Print(stream);
    stream << "];" <<std::endl;
}



} // namespace ast
