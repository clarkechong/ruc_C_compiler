#include "ast_context.hpp"
#include <iostream>

namespace ast{

Context::Context(){}


void Context::AllocateVariable(const std::string& name)  {
    symbolTable_.AllocateVariable(name,offset_);
    offset_ -= 4;
}


int Context::GetVariableOffset(const std::string& name) const {
    return symbolTable_.GetVariableOffset(name);
}

}
