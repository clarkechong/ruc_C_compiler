/*
    DECLARATION CLASS TO CONTAIN:
        - type_specifier node
        - declarator
            - id
        - value (NOT REQUIRED TO BE INITIALIZED)
    
    e.g. int x = 5;
        - type_specifier = int
        - declarator = `x` node
            - id = "x"
        - value = 5

    hence this declaration class is inclusive of INITIALIZING DECLARATIONS.
    this class is also intended for use in function parameters e.g. void myFunc (int x, char y);
    such that parameter `int x` is classed as a (non-initializing) declaration.
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
        Declaration(NodePtr type, NodePtr declarator)
        : type_(std::move(type)), declarator_(std::move(declarator)) {};
        
        Declaration(NodePtr type, NodePtr declarator, NodePtr value)
        : type_(std::move(type)), declarator_(std::move(declarator)), value_(std::move(value)) {};

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;


    private:
        NodePtr type_;
        NodePtr declarator_;
        NodePtr value_;
};

} // namespace ast