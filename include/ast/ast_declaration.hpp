/*
    DECLARATION CLASS TO CONTAIN:
        - type_specifier node
        - declarator
            - id
    
    e.g. int x;
        - type_specifier = int
        - declarator = `x` node
            - id = "x"

    Note: Initialization is now handled by InitDeclarator
    This class is also intended for use in function parameters e.g. void myFunc (int x, char y);
    such that parameter `int x` is classed as a declaration.
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class Declaration : public Node 
{
    public:
        Declaration(NodePtr type, NodePtr declarator);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;


    private:
        NodePtr type_;
        NodePtr declarator_;
};

} // namespace ast