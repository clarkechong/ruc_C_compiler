#include "ast_symboltable.hpp"
#include <iostream>

namespace ast{

void SymbolTable::AllocateVariable(const std::string& name, TypeSpecifier type) {
    int offset = table_.size() * -4;
    table_[name] = {type, offset};
}

int SymbolTable::GetVariableOffset(const std::string& name) const {
    if (table_.find(name) != table_.end()) {
        return table_.at(name).offset;
    }
    throw std::runtime_error("Variable not found: " + name);
}

TypeSpecifier SymbolTable::GetType(const std::string& name) const{
    if (table_.find(name) != table_.end()) {
        return table_.at(name).type;
    }
    throw std::runtime_error("Variable not found: " + name);
}

}

