#include "ast/ast_nodelist.hpp"
#include "ast/ast_declaration.hpp"

namespace ast {

NodeList::NodeList(NodePtr first_node)
{nodes_.push_back(std::move(first_node));}

void NodeList::EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const
{
    for (const auto& node : nodes_) {
        if (node) {
            node->EmitRISCV(stream, dst_reg, context);
        }
    }
}

void NodeList::Print(std::ostream &stream, indent_t indent) const
{
    for (const auto& node : nodes_) {
        if (node) {
            node->Print(stream, indent);
        }
    }
}

void NodeList::PrintParameters(std::ostream &stream) const
{
    // Print parameter list with commas between parameters
    for (size_t i = 0; i < nodes_.size(); ++i) {
        if (nodes_[i]) {
            // Try to cast to Declaration and use PrintAsParameter
            Declaration* decl = dynamic_cast<Declaration*>(nodes_[i].get());
            if (decl) {
                decl->PrintAsParameter(stream);
            } else {
                // Fallback to regular print with zero indent
                nodes_[i]->Print(stream, indent_t(0));
            }
            
            // Add comma between parameters, but not after the last one
            if (i < nodes_.size() - 1) {
                stream << ", ";
            }
        }
    }
}

void NodeList::Push(NodePtr node)
{
    nodes_.push_back(std::move(node));
}

int NodeList::GetNodeCount() const
{
    return nodes_.size();
}

} // namespace ast