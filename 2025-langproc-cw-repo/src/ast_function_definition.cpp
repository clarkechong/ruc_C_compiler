#include "ast_function_definition.hpp"

namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, Context& context) const
{
    // Emit assembler directives.
    // TODO: these are just examples ones, make sure you understand
    // the concept of directives and correct them.
    stream << ".text" << std::endl;
    stream << ".globl ";
    declarator_->Print(stream);
    stream << std::endl;

    declarator_->EmitRISC(stream, context);

    stream << "addi    sp,sp,-32" <<std::endl;
    stream << "sw      s0,28(sp)" <<std::endl;
    stream << "addi    s0,sp,32" <<std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context);
    }

    stream << "lw      s0,28(sp)" <<std::endl;
    stream << "addi    sp,sp,32" << std::endl;
    stream << "jr ra" << std::endl;

}

void FunctionDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}


}
