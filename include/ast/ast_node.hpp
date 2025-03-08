#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast_context.hpp"

namespace ast {

class Node {
    public:
        virtual ~Node();
    
        virtual void emitRISCV(std::ostream& stream, Context& context) const = 0;
        virtual void print(std::ostream& stream) const = 0;
};

using NodePtr = std::unique_ptr<const Node>;

} // namespace ast
