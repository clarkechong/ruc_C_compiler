#include "ast/primary/ast_char.hpp"

namespace ast {

const std::unordered_map<char, char> Char::escape_sequences_ = {
    {'a', '\a'},
    {'b', '\b'},
    {'f', '\f'},
    {'n', '\n'},
    {'r', '\r'},
    {'t', '\t'},
    {'v', '\v'},
    {'0', '\0'},
    {'\\', '\\'},
    {'\'', '\''},
    {'\"', '\"'},
    {'?', '\?'}
};

Char::Char(std::string value) {
    if (value[1] == '\\') {
        auto it = escape_sequences_.find(value[2]);
        if (it != escape_sequences_.end()) {
            value_ = it->second;
        } else {
            throw std::runtime_error("invalid escape sequence");
        }
    } else if (value.size() != 3) {
        throw std::runtime_error("char literal must be a single character");
    } else {
        value_ = value[1];
    }
}

void Char::EmitRISCV(std::ostream& stream, const std::string& dst_reg, Context& context) const 
{
}

void Char::Print(std::ostream& stream, int indent) const 
{
    stream << '\'' << value_ << '\'';
}

} // namespace ast
