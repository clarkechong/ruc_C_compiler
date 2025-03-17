#pragma once
#include "ast_symboltable.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>


namespace ast {
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).
class Context {
    private:
        std::vector <SymbolTable> symbolTable_;
        int currentsymboltable = 0;
        int offset_ = -20;
        int branch_enum = 2;
        int reggie = -1;
        int argie = -1;

    public:
        Context();

        void newsymboltable();

        void AllocateVariable(const std::string& name) ;

        int GetVariableOffset(const std::string& name) const ;

        int Branchoffset();

        int Paramreg();

        int Argreg();
};

} // namespace ast
