#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast_context.hpp"

namespace ast {

class Node 
{
    public:
        virtual ~Node();

        virtual void EmitRISCV(std::ostream& stream, Context& context) const = 0;
        virtual void Print(std::ostream& stream) const = 0;
};

using NodePtr = std::unique_ptr<Node>;

} // namespace ast
