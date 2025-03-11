#include "ast_context.hpp"
#include "Operators/Comparison/ast_geq.hpp"
#include <sstream>

namespace ast {

void Geq::EmitRISC(std::ostream& stream, Context& context) const
{
    left_->EmitRISC(stream,context);
    stream << "add      a4,a5,0" <<std::endl;
    right_->EmitRISC(stream,context);
    stream << "slt      a5,a4,a5" <<std::endl;
    stream << "xori     a5,a5,1"<<std::endl;
    stream << "andi     a5,a5,0xff" <<std::endl;
}

void Geq::Print(std::ostream& stream) const
{
    left_->Print(stream);
    stream << " >= ";
    right_->Print(stream);
}



} // namespace ast
