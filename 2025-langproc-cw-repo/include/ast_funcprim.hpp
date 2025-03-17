#pragma once

#include "ast_node.hpp"
#include "ast_symboltable.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"


// using StringPtr = std::unique_ptr<const String>;

namespace ast {

class Funcprim : public Node
{
private:
    NodePtr declarator_;
    NodePtr parameter_list_;

public:
    Funcprim(NodePtr declarator, NodePtr parameter_list) : declarator_(std::move(declarator)), parameter_list_(std::move(parameter_list)){};
    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};


} // namespace ast
