#include "ast_context.hpp"
#include <iostream>

namespace ast{

Context::Context() : stackPointer_(0) {}

void Context::AllocateVariable(const std::string& name, TypeSpecifier type)  {
    stackPointer_ -= 4;
    symbolTable_.AllocateVariable(name,type);
}


int Context::GetVariableOffset(const std::string& name) const {
    return symbolTable_.GetVariableOffset(name);
}

}
