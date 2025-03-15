#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


namespace ast {

class ParamDecl : public Node
{
private:
    const TypeSpecifier declaration_specifiers_;
    NodePtr declarator_;
public:
    ParamDecl(TypeSpecifier declaration_specifiers, NodePtr declarator) : declaration_specifiers_(declaration_specifiers), declarator_(std::move(declarator)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;


};


} // namespace ast
