#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class FunctionCall : public Node 
{
    public:
        FunctionCall();
        FunctionCall(NodePtr function, NodePtr arguments);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, int indent) const override;


    private:
        NodePtr function_; // The function identifier or expression
        NodePtr arguments_; // The function arguments (a NodeList)
};

} // namespace ast
