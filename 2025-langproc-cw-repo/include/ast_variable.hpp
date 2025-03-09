#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


namespace ast {

class Variable : public Node
{
private:
    TypeSpecifier type_;
    std::string identifier_;

public:
    Variable(TypeSpecifier type, std::string identifier) : type_(type), identifier_(identifier){};

    void EmitRISC(std::ostream& stream, Context& context) const override;

    void Print(std::ostream& stream) const override;

    std::string getid() const;


};


} // namespace ast
