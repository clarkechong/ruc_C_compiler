#pragma once


#include "ast_type_specifier.hpp"

#include <unordered_map>
#include <string>
#include <stdexcept>



namespace ast{



class SymbolTable {
private:
    std::unordered_map<std::string, int> table_;
public:
    void AllocateVariable(const std::string& name, int offset_) ;
    int GetVariableOffset(const std::string& name) const ;
    TypeSpecifier GetType(const std::string& name) const;
};

}
