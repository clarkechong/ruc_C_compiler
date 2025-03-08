#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast_context.hpp"

namespace ast {

class NodeList : public Node {
    public:
        NodeList(NodePtr first_node);

        virtual void emitRISCV(std::ostream& stream, Context& context) const override;
        virtual void print(std::ostream& stream) const override;
    
    private:
        std::vector<NodePtr> nodes_;
};

} // namespace ast
