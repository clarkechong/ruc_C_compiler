#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"
#include "ast/type/ast_type_specifier.hpp"

namespace ast {

class DeclarationType : public Node 
{
    public:
        DeclarationType(TypeSpecifier type);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;


    private:
        TypeSpecifier type_;
};

} // namespace ast