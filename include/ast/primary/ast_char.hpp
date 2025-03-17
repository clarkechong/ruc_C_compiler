#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>

#include "ast/ast_node.hpp"
#include "ast/ast_context.hpp"

namespace ast {

class Char : public Node 
{
    public:
        Char(std::string value);

        virtual void EmitRISCV(std::ostream &stream, const std::string &dst_reg, Context &context) const override;
        virtual void Print(std::ostream &stream, indent_t indent) const override;


    private:
        char value_;
        static const std::unordered_map<char, char> escape_sequences_;
};

} // namespace ast