#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_context.hpp"

namespace ast {

class Node 
{
    public:
        virtual ~Node();

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const = 0;
        virtual void Print(std::ostream &stream, indent_t indent) const = 0;
};

using NodePtr = std::unique_ptr<Node>;

} // namespace ast
