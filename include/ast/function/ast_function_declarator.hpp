#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/ast_declarator.hpp"

namespace ast {

class FunctionDeclarator : public Declarator 
{
    public:
        FunctionDeclarator();

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;
        virtual std::string GetID() const override;

    private:
        ;
};

} // namespace ast