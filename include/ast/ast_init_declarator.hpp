#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class InitDeclarator : public Declarator 
{
    public:
        InitDeclarator();
        InitDeclarator(NodePtr declarator, NodePtr initializer);
        virtual ~InitDeclarator() = default;

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;
        virtual std::string GetID() const override;

    private:
        NodePtr declarator_;
        NodePtr initializer_;
};

} // namespace ast