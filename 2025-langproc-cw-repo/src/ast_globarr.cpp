#include "ast_globarr.hpp"
#include "ast_context.hpp"
#include <sstream>


namespace ast {

void GlobArr::EmitRISC(std::ostream& stream, Context& context) const
{
    declarator_->Print(stream);
    stream << ":" <<std::endl;
    (void)context;
    std::ostringstream badworkaround;
    size_->Print(badworkaround);
    std::string size = badworkaround.str();
    int coolsize = std::stoi(size) * 4;

    if(size_ == nullptr){
        stream << ".zero    4" <<std::endl;
    }
    else{
        stream << ".zero     " << coolsize <<std::endl;
    }
}

void GlobArr::Print(std::ostream& stream) const
{
   stream << declaration_specifiers_ << " ";
   declarator_->Print(stream);
   if(size_ != nullptr){
    stream << "[";
    size_->Print(stream);
    stream << "];" <<std::endl;
   }
   else{
    stream << "[];"<<std::endl;
   }
}



} // namespace ast
