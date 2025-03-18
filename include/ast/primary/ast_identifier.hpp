#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/ast_declarator.hpp"

namespace ast {

class Identifier : public Declarator 
{
    public:
        Identifier(std::string id);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;
        virtual std::string GetID() const override;

    private:
        std::string id_;
};

} // namespace ast