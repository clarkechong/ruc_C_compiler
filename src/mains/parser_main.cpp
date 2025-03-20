/*
    TEST PARSER FUNCTIONALITY:
        - READ in from input txt
        - MATCH INPUT with parser grammar rules
        - which also means executing any actions associated with a rule match
        
        - if invalid syntax (i.e. no grammar rules match), yyerror() is called
*/

#include <stdio.h>
#include <iostream>
#include "ast.hpp"

int main(int argc, char** argv) {

    ast::Context context;

    auto root = ParseAST(argv[1]);
    root->EmitRISCV(std::cout, "a0", context);

    return 0;
    
}