#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast/ast_node.hpp"
#include "ast/ast_nodelist.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class ArrayInitList : public NodeList 
{
    public:
        ArrayInitList(NodePtr first_element);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;

    private:
        void RecursiveEmit(std::ostream &stream, const std::string &base_ptr_reg, 
                          Context &context, TypeSpecifier type, 
                          int &offset) const;
};

} // namespace ast