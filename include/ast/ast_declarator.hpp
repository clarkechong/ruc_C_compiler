#pragma once

#include "ast/ast_node.hpp"

namespace ast {

/*
    ABSTRACT CLASS FOR NON-ANONYMOUS DECLARATORS.
    All declarators, if not anonymous, must contain an ID.
*/

class Declarator : public Node 
{
    public:
        virtual ~Declarator() {};

        virtual std::string GetID() const = 0;

};

} // namespace ast
