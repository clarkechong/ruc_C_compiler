#include "ast_symboltable.hpp"
#include <iostream>

namespace ast{

void SymbolTable::AllocateVariable(const std::string& name, int offset) {
    table_[name] = offset;
}

int SymbolTable::GetVariableOffset(const std::string& name) const {
    auto it = table_.find(name);
    if (it != table_.end()) {
        return it->second;
    }
    else{
    throw std::runtime_error("Variable not found: " + name);
    }
}

}

