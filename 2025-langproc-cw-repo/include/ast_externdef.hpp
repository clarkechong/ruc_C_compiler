#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


// using StringPtr = std::unique_ptr<const String>;

namespace ast {

class Externdef : public Node
{
private:
    TypeSpecifier type_;
    NodePtr identifier_;

public:
    Externdef(TypeSpecifier type, NodePtr identifier) : type_(type), identifier_(std::move(identifier)){};
    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};


} // namespace ast
