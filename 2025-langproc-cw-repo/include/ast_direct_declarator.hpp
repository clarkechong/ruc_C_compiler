#pragma once

#include "ast_node.hpp"

namespace ast {

class DirectDeclarator : public Node
{
private:
    NodePtr identifier_;
    NodePtr param_list_;

public:
    DirectDeclarator(NodePtr identifier, NodePtr param_list) : identifier_(std::move(identifier)),param_list_(std::move(param_list)){};

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
