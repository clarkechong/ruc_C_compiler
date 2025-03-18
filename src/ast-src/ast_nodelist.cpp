#include "ast/ast_nodelist.hpp"

namespace ast {

NodeList::NodeList(NodePtr first_node) {
    nodes_.push_back(std::move(first_node));
}

void NodeList::EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const {
    for (const auto& node : nodes_) {
        if (node) {
            node->EmitRISCV(stream, dst_reg, context);
        }
    }
}

void NodeList::Print(std::ostream &stream, indent_t indent) const {
    for (const auto& node : nodes_) {
        if (node) {
            node->Print(stream, indent);
            
            // if not the last node and not printing in a block context, add a separator
            if (node != nodes_.back()) {
                stream << ", ";
            }
        }
    }
}

void NodeList::Push(NodePtr node) {
    nodes_.push_back(std::move(node));
}

int NodeList::GetNodeCount() const {
    return nodes_.size();
}

} // namespace ast