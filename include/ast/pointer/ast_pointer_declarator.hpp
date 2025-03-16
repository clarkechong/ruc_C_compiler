#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class PointerDeclarator : public Declarator 
{
    public:
        PointerDeclarator();

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;
        virtual std::string GetID() const override;

    private:
        ;
};

} // namespace ast