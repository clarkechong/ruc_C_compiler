#pragma once
#include "ast_symboltable.hpp"
#include <iostream>
#include <unordered_map>


namespace ast {
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).
class Context {
    private:
        SymbolTable symbolTable_;
        int offset_ = -20;

    public:
        Context();

        void AllocateVariable(const std::string& name) ;

        int GetVariableOffset(const std::string& name) const ;
};

} // namespace ast
