#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


namespace ast {

class Variable : public Node
{
private:
    std::string name_;
    TypeSpecifier vartype_;

public:
    Variable(const std::string& name, TypeSpecifier vartype) : name_(name), vartype_(vartype) {}

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

    TypeSpecifier GetType(const SymbolTable& table) const ;

    const std::string GetName() const ;
};

} // namespace ast
