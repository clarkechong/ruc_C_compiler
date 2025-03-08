#include "ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, Context&) const
{
    int u12i = value_ >> 12 ;
    int u12 = u12i  << 12;
    int l12 = value_ & 0xFFF;
    if ( value_ > 4095) {
        stream << "li a5, " << u12 << std::endl;
        stream << "addi a5,a5," << l12 << std::endl;
    }
    else{
        stream << "li a5, " << value_ << std::endl;
    }

}

void IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

// int IntConstant::Getvalue (std::ostream& stream) const
// {
//     return value_;
// }


} // namespace ast
