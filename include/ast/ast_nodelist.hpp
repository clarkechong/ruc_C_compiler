#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast_node.hpp"
#include "ast_context.hpp"

namespace ast {

class NodeList : public Node 
{
    public:
        NodeList(NodePtr first_node);

        virtual void EmitRISCV(std::ostream& stream, Context& context) const override;
        virtual void Print(std::ostream& stream) const override;

    private:
        std::vector<NodePtr> nodes_;
};

} // namespace ast
