#include "ast_context.hpp"
#include <iostream>

namespace ast{

Context::Context(){
    symbolTable_.emplace_back();
}


void Context::newsymboltable(){
    currentsymboltable++;
    symbolTable_.emplace_back();
    offset_ = -20;
    branch_enum = 2;
    reggie = -1;
    argie = -1;
}

void Context::AllocateVariable(const std::string& name)  {
    symbolTable_[currentsymboltable].AllocateVariable(name,offset_);
    offset_ -= 4;
}


int Context::GetVariableOffset(const std::string& name) const {
    return symbolTable_[currentsymboltable].GetVariableOffset(name);
}

int Context::Branchoffset() {
    branch_enum++;
    return branch_enum;
}

int Context::Paramreg(){
    reggie++;
    return reggie;
}

int Context::Argreg(){
    argie++;
    return argie;
}

}
