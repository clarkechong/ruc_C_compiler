#pragma once


#include "ast_type_specifier.hpp"

#include <unordered_map>
#include <string>
#include <stdexcept>



namespace ast{

struct Variableinfo{
    TypeSpecifier type;
    int offset;
};

class SymbolTable {
private:
    std::unordered_map<std::string, Variableinfo> table_;

public:
    void AllocateVariable(const std::string& name, TypeSpecifier type) ;
    int GetVariableOffset(const std::string& name) const ;
    TypeSpecifier GetType(const std::string& name) const;
};

}
