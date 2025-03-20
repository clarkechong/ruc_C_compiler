#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class ArrayDeclarator : public Declarator
{
    public:
        ArrayDeclarator();
        ArrayDeclarator(NodePtr direct_declarator, NodePtr constant_expression);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;
        virtual std::string GetID() const override;
        std::vector<int> GetArrayIndexSpecifiers() const;

    private:
        NodePtr direct_declarator_;
        NodePtr constant_expression_;
};

} // namespace ast