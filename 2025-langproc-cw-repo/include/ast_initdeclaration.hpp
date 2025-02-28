#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


namespace ast {

class InitDecl : public Node
{
private:
    const TypeSpecifier declaration_specifiers_;
    NodePtr declarator_;
    NodePtr value_;
public:
    InitDecl(TypeSpecifier declaration_specifiers, NodePtr declarator, NodePtr value) : declaration_specifiers_(declaration_specifiers), declarator_(std::move(declarator)),value_(std::move(value)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;


};


} // namespace ast
