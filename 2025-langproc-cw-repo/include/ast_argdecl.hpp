#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


namespace ast {

class Argdecl : public Node
{
private:
    NodePtr expression_;
public:
    Argdecl(NodePtr expression) : expression_(std::move(expression)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;


};


} // namespace ast
