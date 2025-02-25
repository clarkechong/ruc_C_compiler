#include "ast_symboltable.hpp"
#include <iostream>

namespace ast{

void SymbolTable::AllocateVariable(const std::string& name, TypeSpecifier type) {
    int offset = symbols_.size() * -4;
    symbols_[name] = {type, offset};
}

int SymbolTable::GetVariableOffset(const std::string& name) const {
    if (symbols_.find(name) != symbols_.end()) {
        return symbols_.at(name).offset;
    }
    throw std::runtime_error("Variable not found: " + name);
}

TypeSpecifier SymbolTable::GetType(const std::string& name) const{
    if (symbols_.find(name) != symbols_.end()) {
        return symbols_.at(name).type;
    }
    throw std::runtime_error("Variable not found: " + name);
}

}

