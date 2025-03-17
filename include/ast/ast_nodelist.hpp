#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class NodeList : public Node 
{
    public:
        NodeList(NodePtr first_node);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;
        void PrintParameters(std::ostream &stream) const;

        virtual void Push(NodePtr node);
        virtual int GetNodeCount() const;

    private:
        std::vector<NodePtr> nodes_;
};

using NodeListPtr = std::unique_ptr<NodeList>;

} // namespace ast
